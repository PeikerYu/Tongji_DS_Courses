/* 2451951 大数据 于沛可 */

#include <cstdio>   //NULL
//不再允许包含任何系统头文件

/* ----- 不允许定义任何形式的全局变量/全部数组/只读全局变量/宏定义!!!!! ----- */

/* 函数实现部分，{ }内的东西可以任意调整，目前的return只是一个示例，可改变 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strlen(const char* str)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return 0;
    int len=0;
    const char* p = str;
    for (; *p != '\0'; p++)
    {
        len++;
    }
    return len;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strcat(char* s1, const char* s2)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
        return s1;
    char* original_s1 = s1;
    int len = tj_strlen(s1);
    s1 += len;
    for (;*s2 != '\0'; s1++, s2++)
    {
        *s1 = *s2;
    }
    *s1 = '\0';
    return original_s1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strncat(char* s1, const char* s2, const int len)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
        return s1;
    char* original_s1 = s1;
    int s1_len = tj_strlen(s1);
    s1 += s1_len;
    int count = 0;
    for (; *s2 != '\0' && count < len; s1++, s2++, count++)
    {
        *s1 = *s2;
    }
    *s1 = '\0';
    return original_s1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strcpy(char* s1, const char* s2)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
    {
        *s1 = '\0';   // 复制“空串”
        return s1;
    }
    char* original_s1 = s1;
	while (1)
    {
        *s1 = *s2;
        if (*s2 == '\0')
            break;
        s1++;
        s2++;
    }
    return original_s1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明： 
***************************************************************************/
char* tj_strncpy(char* s1, const char* s2, const int len)
{
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
        return s1;
    char* original_s1 = s1;
    int count = 0;
	while (count < len && *s2 != '\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
        count++;
    }
    return original_s1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcmp(const char* s1, const char* s2)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (s1 == NULL && s2 != NULL)
        return -1;
    if (s2 == NULL && s1 != NULL)
        return 1;
    if (s1 == NULL && s2 == NULL)
        return 0;
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcasecmp(const char* s1, const char* s2)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL && s2 != NULL)
        return -1;
    if (s2 == NULL && s1 != NULL)
        return 1;
    if (s1 == NULL && s2 == NULL)
        return 0;
    char c1, c2;
    while (*s1 != '\0' && *s2 != '\0')
    {
        c1 = *s1;
        if (c1 >= 'A' && c1 <= 'Z')
            c1 = c1 + ('a' - 'A'); // 大写转小写
        c2 = *s2;
        if (c2 >= 'A' && c2 <= 'Z')
            c2 = c2 + ('a' - 'A'); // 大写转小写
        if (c1 != c2)
        {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    c1 = *s1;
    if (c1 >= 'A' && c1 <= 'Z')
        c1 = c1 + ('a' - 'A'); // 大写转小写
    c2 = *s2;
    if (c2 >= 'A' && c2 <= 'Z')
        c2 = c2 + ('a' - 'A'); // 大写转小写
    return c1 - c2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strncmp(const char* s1, const char* s2, const int len)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL && s2 != NULL)
        return -1;
    if (s2 == NULL && s1 != NULL)
        return 1;
    if (s1 == NULL && s2 == NULL)
        return 0;
    int count = 0;
	while (count < len)
    {
        if (*s1 != *s2)
            return *s1 - *s2;
		if (*s1 == '\0' && *s2 == '\0')
            return 0;
        s1++;
        s2++;
        count++;
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcasencmp(const char* s1, const char* s2, const int len)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (s1 == NULL && s2 != NULL)
        return -1;
    if (s2 == NULL && s1 != NULL)
        return 1;
    if (s1 == NULL && s2 == NULL)
        return 0;
    int count = 0;
    char c1, c2;
    while (count < len)
    {
        c1 = *s1;
        if (c1 >= 'A' && c1 <= 'Z')
            c1 = c1 + ('a' - 'A'); // 大写转小写
        c2 = *s2;
        if (c2 >= 'A' && c2 <= 'Z')
            c2 = c2 + ('a' - 'A'); // 大写转小写
        if (c1 != c2)
        {
            return c1 - c2;
        }
        if (*s1 == '\0' && *s2 == '\0')
            return 0;
        s1++;
        s2++;
        count++;
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strupr(char* str)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return NULL;
    char* original_str = str;
    while (*str != '\0')
    {
        if (*str >= 'a' && *str <= 'z')
            *str += 'A' - 'a';
        str++;
    }
    return original_str;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strlwr(char* str)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return NULL;
    char* original_str = str;
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
            *str += 'a' - 'A';
        str++;
    }
    return original_str;
    return str;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strchr(const char* str, const char ch)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return 0;
	for (int i = 0; *str != '\0'; str++, i++)
    {
        if (*str == ch)
            return i + 1;
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strstr(const char* str, const char* substr)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL || substr == NULL)
        return 0;
    if (*substr == '\0') 
    {
        return 1;
    }
    const char* original_str = str; //original_str为str中第一个字符

    for (; *str != '\0'; str++)
    {
        const char* q_str = str; //q为当前循环中str的位置
        const char* q_substr = substr; //p为substr中第一个字符

        if (*str == *q_substr) //str中找到与substr相等的第一个字符
        {
            bool tag = 1;
            while (*q_substr != '\0')
            {
                if (*q_substr != *q_str)
                {
                    tag = 0;
                    break;
                }
                q_substr++;
                q_str++;
            }
            if (tag == 1)
				return str - original_str + 1;
        }
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrchr(const char* str, const char ch)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return 0;
    int len = tj_strlen(str);
	str += len - 1;
    for (int i = len - 1; i >= 0; i--)
    {
        if (*str == ch)
            return i + 1;
        str--;
    }
    return 0;
    //const char* str 限制了不能通过 str 指针修改它所指向的字符内容，但并没有限制修改 str 指针变量本身存储的地址
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrstr(const char* str, const char* substr)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL || substr == NULL) 
        return 0;
    const char* str_end = str;
    while (*str_end != '\0') 
    {
        str_end++;
    }
    const char* substr_end = substr;
    const char* original_str = str; // 记录主串起始地址
    while (*substr_end != '\0') 
    {
        substr_end++;
    }
    if ((str_end - str) < tj_strlen(substr)) 
    {
        return 0; // 主串比子串短
    }
    const char* p_match_start = str_end;
    p_match_start -= tj_strlen(substr); 
    while (p_match_start >= original_str)
    {
        const char* q_str = p_match_start;
        const char* q_substr = substr;
        bool tag = 1;
        while (*q_substr != '\0')
        {
            if (*q_str != *q_substr)
            {
                tag = 0;
                break;
            }
            q_str++;
            q_substr++;
        }
        if (tag==1)
        {
            return (p_match_start - original_str) + 1;
        }
        p_match_start--; 
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strrev(char* str)
{
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    if (str == NULL)
        return NULL;
	if (*str == '\0')
        return str;
    char* original_str = str;
    char* begin = str;
    char* end = str + tj_strlen(str)-1;
    char tmp;
    while (begin < end)
    {
        tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
        end--;
    }
    return original_str;
}