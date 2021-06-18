一、概述
    所有执行I/O操作的系统调用都以文件描述符(一个非负整数)，来指代打开的文件。

    文件描述符     用途       POSIX名称         stdio流
        0       标准输入     STDIN_FILENO       stdin
        1       标准输出     STDOUT_FILENO      stdout
        2       标准错误     STDERR_FILENO      stderr
    
    主要系统调用:
        fd = open(pathname, flags, mode)
            pathname: 标识文件
            flags： 指定文件的打开方式
            mode：指定由 open() 创建文件的访问权限，如果未创建，可忽略该参数。