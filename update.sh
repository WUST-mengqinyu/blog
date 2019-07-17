#!/bin/bash
cd blog && mkdocs gh-deploy
cd /home/badcw/PycharmProjects/blog && git pull
cd /home/badcw/PycharmProjects/blog && git add *
timenow=$(date)" badcw"
cd /home/badcw/PycharmProjects/blog && git commit -m "${timenow}"
cd /home/badcw/PycharmProjects/blog && git push