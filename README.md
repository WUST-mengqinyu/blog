## 项目说明

使用 Mkdocs 进行队伍 WIKI 的搭建，为WUSTACM 2019年一队的 WIKI，欢迎Star Or Fork

## 项目链接

https://wiki.badcw.cn/

## Mkdocs 模板使用教程

如果想使用相同的主题和配置

直接运行 

```bash
pip3 install -r requirements.txt
```

即可安装 `Mkdocs` 及 `mkdocs.yml` 配置中的插件

复制了 `mkdocs.yml` 其他内容就可以自己写了

注意 `mkdocs.yml` 中的各种参数可能就随便改一下就能用

简单指令：

- `mkdocs serve` 在本地重新编译本项目并运行

    如果默认 8000 端口无法使用可以用 --dev-addr 添加端口参数：例如 `mkdocs serve --dev-addr 127.0.0.1:8088`

    支持动态修改预览 .md 渲染效果

- `mkdocs gh-deploy` 上传到 github 的 gh-pages branch（只要配置好了`repo_name`字段一键化创建上传，不需要手动操作git）

- `mkdocs build` 生成静态文件（mkdocs是纯静态的网站）

- 另外的指令可参考 [mkdocs官网](https://www.mkdocs.org/)

如果想用 Github Pages 直接做 site：

在 github 项目 settings 中选择 gh-pages branch 做 source，填写你自己申请的域名或者是github默认域名 `id.github.io` 即可访问


