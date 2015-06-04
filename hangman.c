/*
悬挂小人游戏

main.c
------------

游戏的主体代码

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

int win(int letterFound[], long wordSize);
int researchLetter(char letter, char secretWord[], int letterFound[]);
char readCharacter();

int main(int argc, char* argv[])
{
    char letter = 0; // 存储用户输入的字母
    char secretWord[100] = {0}; // 要猜测的单词
    int *letterFound = NULL; // 布尔值的数组. 数组的每一个元素对应猜测单词的一个字母。 0 = 还没猜到此字母, 1 = 已猜到字母
    int leftTimes = 7; // 剩余猜测次数 (0 = 失败)
    int i = 0; // 下标
    long wordSize = 0;  // 单词的长度（字母数目）

    printf("欢迎来到悬挂小人游戏！\n");

    // 从词库（文件dictionary）中随机选取一个单词
    if (!chooseWord(secretWord))
      exit(0); // 退出游戏

    // 获取单词的长度
    wordSize = strlen(secretWord);

    letterFound = malloc(wordSize * sizeof(int)); // 动态分配数组的大小，因为我们一开始不知道单词长度
    if (letterFound == NULL)
      exit(0);

    // 初始化布尔值数组，都置为0，表示还没有字母被猜到
    for (i = 0 ; i < wordSize ; i++)
      letterFound[i] = 0;

    // 主while循环，如果还有猜测机会并且还没胜利，继续
    while(leftTimes > 0 && !win(letterFound, wordSize)){
      printf("\n\n您还剩 %d 次机会", leftTimes);
      printf("\n神秘单词是什么呢 ? ");

      /* 我们显示猜测的单词，将还没猜到的字母用*表示
        例如 : *O**LE */
      for (i = 0 ; i < wordSize ; i++)
      {
	if (letterFound[i]) // 如果第i+1个字母已经猜到
	  printf("%c", secretWord[i]); // 打印出来
	else
	  printf("*"); // 还没猜到，打印一个*
      }

      printf("\n输入一个字母 : ");
      letter = readCharacter();

      // 如果用户输入的字母不存在于单词中
      if (!researchLetter(letter, secretWord, letterFound))
      {
	leftTimes--; // 将剩余猜测机会数减1
      }
    }

    if (win(letterFound, wordSize))
      printf("\n\n胜利了! 神秘单词是 : %s\n", secretWord);
    else
      printf("\n\n失败了! 神秘单词是 : %s\n", secretWord);

    return 0;
}

// 判断是否胜利
int win(int letterFound[], long wordSize)
{
    int i = 0;
    int win = 1; // 1为胜利，0为失败

    for (i = 0 ; i < wordSize ; i++)
    {
        if (letterFound[i] == 0)
            win = 0;
    }

    return win;
}

// 在所要猜的单词中查找用户输入的字母
int researchLetter(char letter, char secretWord[], int letterFound[])
{
    int i = 0;
    int correctLetter = 0; // 0表示字母不在单词里，1表示字母在单词里

    // 遍历单词数组secretWord，以判断所猜字母是否在单词中
    for (i = 0 ; secretWord[i] != '\0' ; i++)
    {
        if (letter == secretWord[i]) // 如果字母在单词中
        {
            correctLetter = 1; // 表示猜对了一个字母
            letterFound[i] = 1; // 对于所有等于所猜字母的数组位置，都将其数值变为1
        }
    }

    return correctLetter;
}

char readCharacter()
{
  char character = 0;

  character = getchar(); // 读取一个字母
  character = toupper(character); // 把这个字母转成大写

  // 读取其他的字符，直到 \n (为了忽略它)
  while(getchar() != '\n')
    ;

  return character; // 返回读到的第一个字母
}
