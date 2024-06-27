#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <iterator>
#include <fstream> // 包含对ifstream的定义

// 执行命令
void executeCommand(const std::vector<std::string>& cmd) {
    // 创建char*数组用于execvp
    std::vector<char*> argv;
    for (const auto& arg : cmd) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // execvp需要一个以nullptr结尾的参数列表

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子进程
        execvp(argv[0], argv.data());
        perror("execvp");
        _exit(EXIT_FAILURE);
    } else {
        // 父进程
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Command executed with exit status " << WEXITSTATUS(status) << std::endl;
        }
    }
    if (cmd[0] == "exit") {
        // 直接退出程序
        exit(0);
        return;
    }
}

// 执行脚本
void executeScript(const std::string& scriptPath) {
    std::ifstream script(scriptPath);
    if (!script.is_open()) {
        std::cerr << "Failed to open script file: " << scriptPath << std::endl;
        return;
    }

    std::string line;
    while (getline(script, line)) {
        std::vector<std::string> cmd;
        std::istringstream iss(line);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cmd));
        executeCommand(cmd);
    }
    script.close();
}

// 处理I/O重定向
void handleRedirect(const std::vector<std::string>& cmd, const std::string& redirection, bool append = false) {
    int flags = append ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC;
    int fd = open(redirection.c_str(), flags, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd); // 不再需要文件描述符

    executeCommand(cmd);
}

// 处理管道
void handlePipe(const std::vector<std::string>& cmd1, const std::vector<std::string>& cmd2) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return;
    }

    if (pid1 == 0) {
        // 子进程1：写入端
        close(pipefd[0]); // 关闭读端
        dup2(pipefd[1], STDOUT_FILENO); // 重定向标准输出到管道写端
        executeCommand(cmd1);
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return;
    }

    if (pid2 == 0) {
        // 子进程2：读取端
        close(pipefd[1]); // 关闭写端
        dup2(pipefd[0], STDIN_FILENO); // 重定向标准输入到管道读端
        executeCommand(cmd2);
        exit(EXIT_SUCCESS);
    }

    // 父进程等待子进程结束
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);
    close(pipefd[0]);
    close(pipefd[1]);
}

int main() {
    std::string line;
    while (true) {
        std::cout << "myshell> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

        // 处理重定向
        for (size_t i = 1; i < tokens.size() - 1; ++i) {
            if ((tokens[i] == ">" || tokens[i] == ">>")) {
                bool append = tokens[i] == ">>";
                handleRedirect(tokens, tokens.back(), append);
                return 0;
            }
        }

        // 处理管道
        std::size_t pipePos = line.find("|");
        if (pipePos != std::string::npos) {
            std::string cmd1 = line.substr(0, pipePos);
            std::string cmd2 = line.substr(pipePos + 1);
            std::vector<std::string> tokens1, tokens2;
            std::istringstream iss1(cmd1), iss2(cmd2);
            std::copy(std::istream_iterator<std::string>(iss1), std::istream_iterator<std::string>(), std::back_inserter(tokens1));
            std::copy(std::istream_iterator<std::string>(iss2), std::istream_iterator<std::string>(), std::back_inserter(tokens2));
            handlePipe(tokens1, tokens2);
        } else {
            // 正常执行命令
            executeCommand(tokens);
        }
    }
    return 0;
}
