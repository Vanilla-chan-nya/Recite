# Recite

一个用来**查单词**，**背单词**的程序

## **What can it do?**

它可以当作一本字典，支持查询单词，收藏单词，添加单词及其中文，导入词库，甚至帮您背单词！

## **To-do list**

* [x] 前缀查询(字母顺序优先) prefix query (alphabetic priority)
* [x] 前缀查询(单词长度优先) prefix query (word length first)
* [ ] 近似查询 approximate query
* [ ] 查询所有 query all
* [x] 收藏单词 collect words
* [x] 网络翻译 web translation
* [ ] 下载例句 download sample sentences
* [x] 导入词库 import Thesaurus
* [x] 记忆练习 memory practice
* [ ] 设置 Settings

## Inquire

使用键盘输入单词即可查询。

Use the keyboard to input words to query.

当您的输入发生更改时，下方会出现$15$个候选词 *(候选词数量，优先显示顺序可以在设置中调节)* 。

When your input changes, there are $15$ candidate words below *(The number of candidate words and priority display order can be adjusted in settings.)* .

当您在候选词中找到了您可能想要查询的单词之后，可以按`Tab` *(在您的键盘的左侧)* 进入选词界面。

When you find the words you may want to query in the candidate words, you can press `tab` *(on the left side of your keyboard)* to enter the word selection interface.

按`↑`/``↓``或者`w`/`s`切换选项，选择到您想要查询的单词后按下`回车`就可以将它收藏，再次按下可以取消收藏。

Press `↑`​/ `​↓`​or `w`/`s` to switch options, select the words you want to query, press `enter` to collect them, and press again to cancel the collection.

再次按下`Tab`可以回到单词查询界面。

Press' tab 'again to return to the word query interface.

被收藏的单词会变成 **红色** 以提醒您。

The collected words will turn red to remind you.

有一些快捷键:

There are some shortcuts:

* `0`清空查询框 Clear query box
* `Tab`进入/退出详细释义界面 Enter / exit detailed definition interface
* `1`进入设置 Settings
* `2`在线翻译 web translation
* `3`记忆练习 memory practice

## Practice

主要有两种训练方式

* 显示一个单词和四个随机选项，同时给四个随机的示意，请你在四个选项中选出最佳答案。
* 给你这个单词的示意，请拼出这个单词

但凡曾经有熟练度的单词都有可能被提问。

第一种问题比较简单，适合在低熟练度时使用。

第二种则要到有一定的熟练度时使用。

回答正确，则熟练度增加；

反之，熟练度减少。

|              | 正确correct | 错误error |
| ------------ | ----------- | --------- |
| 选择choice   | +1          | *0.4      |
| 拼写spelling | +5          | *0.6      |

若收藏一个单词，那么这个单词的熟练度会+1，表示你要开始 **Recite** 这个单词了！

### 推荐算法

**首先在生词中随机选一个单词。**

再用熟练度$\omega$进行判别（熟练度高的，成功概率应该降低）
$$
P(\omega)=2^{-\frac{\omega}{50}}\cdot0.9+0.1
$$
若连续$100$次内都是匹配失败，那么就直接随机选一个，并提醒用户 **来点新词** 。



## web translation

按`2`进入 **联网翻译**。

此功能需要百度翻译api支撑。

请到百度开发者页面中认证，并在 `baidu-api.py` 中手动填写APPID和key。

**切忌把自己的APPID和key告诉别人！！！**

## **Mutual encouragement**

**愿共勉之。**

**Let us encourage each other in our endeavours.**

## **LICENSE**

**SATA**

https://github.com/zTrix/zio/blob/master/LICENSE.txt

Thinks