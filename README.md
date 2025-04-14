#SteamLocomotive - Windows 版 sl 命令
SteamLocomotive 是一个将 Linux 系统中的 sl（Steam Locomotive）命令移植到 Windows 平台的工具。sl 是一个非常有趣的命令，通常用于当你误打了 ls 时，显示一列火车动画。本项目的目的是让 Windows 用户也能体验到这个有趣的命令。

项目简介
Linux 中的 sl 命令，通常作为一种调侃的工具，目的是在用户输入错误命令时（如 ls 被误打为 sl）输出一个火车的动画。SteamLocomotive 将这一有趣的命令移植到了 Windows 环境，并以 MSI 安装包 的形式提供给用户，支持快速安装和简单配置。

主要功能
火车动画效果：和 Linux 版 sl 一样，当你输入 sl 命令时，终端将显示火车动画。

简单安装：通过 MSI 安装包，用户只需执行安装，便可以在 Windows 系统中轻松使用 sl 命令。

自动添加到 PATH 环境变量：安装过程中会自动将 sl 所在的安装目录添加到系统的 PATH 环境变量中，使得用户能够在命令行中任意位置直接运行 sl 命令。

可定制安装路径：支持用户选择安装路径，默认路径为 C:\Program Files\SteamLocomotive。

安装步骤
1. 下载安装包
下载并运行 SteamLocomotive.msi 安装包。你可以从项目的 Release 页面获取最新版本的安装包，或者直接从 GitHub 克隆项目并手动构建。

2. 运行安装程序
双击运行下载的 SteamLocomotive.msi 文件，按以下步骤进行安装：

选择安装目录（默认安装到 C:\Program Files\SteamLocomotive）。

选择是否将 sl 添加到系统环境变量 PATH（默认会添加，方便全局使用）。

贡献
如果你希望贡献代码或改进此项目，请按照以下步骤进行：

Fork 仓库：在 GitHub 上点击 Fork 按钮，将项目复制到你的 GitHub 账户中。

创建分支：在你的 Fork 中创建一个新分支，用于进行更改。

提交更改：完成更改后，提交到你的分支。

发送 Pull Request：向主仓库发送 Pull Request，我们会审查并合并你的更改。

联系我们
如果你在使用过程中遇到任何问题，或有任何问题或建议，欢迎通过以下方式联系我：

电子邮件：lawrencemari394@gmail.com

GitHub：https://github.com/Mari-Lawrence

许可证
本项目采用 MIT 许可证，可以自由使用、修改和分发。更多细节请查看 LICENSE 文件
