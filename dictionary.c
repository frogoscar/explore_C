/*
悬挂小人游戏

dictionary.c
------------

这里定义了两个函数：

1. chooseWord   用于每轮从dictionary文件中随机抽取一个单词
2. randomNum    用于返回一个介于 0～单词总数-1 之间的随机数

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dictionary.h"

int chooseWord(char *wordChosen)
{
    FILE* dictionary = NULL; // 指向我们的文件dictionary的文件指针
    int wordNum = 0;         // 单词总数
    int chosenWordNum = 0;   // 选中的单词编号
    int i = 0;               // 下标
    int characterRead = 0;   // 读入的字符

    dictionary = fopen("dictionary", "r"); // 以只读模式打开词库（dictionary文件）
    if (dictionary == NULL) // 如果打开文件不成功
    {
      printf("\n无法装载词库\n");
      return 0; // 返回0表示出错
    }

    // 统计词库中的单词总数，也就是统计回车符 \n 的数目
    do
    {
      characterRead = fgetc(dictionary);
      if (characterRead == '\n')
	wordNum++;
    } while(characterRead != EOF);

    chosenWordNum = randomNum(wordNum); // 随机选取一个单词（编号）

    // 我们重新从文件开始处读取（rewind函数），直到遇到选中的那个单词
    rewind(dictionary);
    while (chosenWordNum > 0)
    {
      characterRead = fgetc(dictionary);
      if (characterRead == '\n')
	chosenWordNum--;
    }

    /* 文件指针已经指向正确位置，我们就用fgets来读取那一行（也就是那个选中的单词）*/
    fgets(wordChosen, 100, dictionary);

    // 放置 \0 字符用于表示字符串结束
    wordChosen[strlen(wordChosen) - 1] = '\0';
    fclose(dictionary);

    return 1;  // 一切顺利，返回1
}

int randomNum(int maxNum)
{
  srand(time(NULL));
  return (rand() % maxNum);
}
