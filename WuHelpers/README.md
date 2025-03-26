# Introduction
Bilibili Personal Homepage：https://space.bilibili.com/381317561

A UE plugin that includes some helper functions

This is a plugin I developed previously and open-sourced on GitHub today.

# Current Features:
Currently, there is only one feature, and new features may be updated periodically in the future.

Two macros are available:
WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES
and
WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION

When a function is called again within its call interval, these macros will throw an error. They are particularly useful in Reliable functions - helping detect accidental rapid calls to Reliable functions that could cause issues.

# Usage
Detailed instructions are already provided in the .h files. Please open the .h files to view them

# UE Version
This plugin can be successfully compiled on UE5 5.5.4. In theory, it should compile successfully on other versions as well. If you encounter compilation issues, please submit a problem in the issues.

# 简介
B站个人主页： https://space.bilibili.com/381317561

一个集合了一些帮助功能的UE插件

这个是我以前开发的插件，今天提交到GitHub开源

# 目前功能：
目前只有一个功能，以后可能会不定期更新功能

有WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES和WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION两个宏可供使用

当函数调用间隔内，再此调用此函数，就会抛出错误。尤其是用在Reliable函数中 - 检查是否有代码因为失误，快速调用Reliable函数导致出现问题。

# 使用
使用方法再.h文件里已经有很详细的描述。请打开.h文件查看。

# UE版本
此插件可以在UE5 5.5.4上编译成功。理论上其他版本也能编译通过，如无法编译通过，请在issues提交问题
