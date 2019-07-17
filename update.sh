#!/bin/bash
cd blog && mkdocs gh-deploy
cd /home/badcw/PycharmProjects/blog && git pull
cd /home/badcw/PycharmProjects/blog && git add *
timenow=$(date)
cd /home/badcw/PycharmProjects/blog && git commit -ma "\"${timenow} badcw\""
cd /home/badcw/PycharmProjects/blog && git push