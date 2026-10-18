/* 2451951 大数据 于沛可 */
#include <iostream>
#include <cstring>
#include "7-b2.h"
#include "cmd_console_tools.h"
using namespace std;

static bool is_chinese(unsigned char c1, unsigned char c2)
{
	return (c1 >= 0xA1 && c1 <= 0xFE) && (c2 >= 0xA1 && c2 <= 0xFE);
}

static int get_display_width(const char* str)
{
	int width = 0;
	for (int i = 0; str[i]; )
	{
		if (is_chinese((unsigned char)str[i], (unsigned char)str[i + 1]))
		{
			width += 2;
			i += 2;
		}
		else
		{
			width += 1;
			i += 1;
		}
	}
	return width;
}

static int count_menu_items(const char menu[][MAX_ITEM_LEN])
{
	int cnt = 0;
	while (menu[cnt][0] != '\0')
		++cnt;
	return cnt;
}

/* 计算实际显示坐标（考虑自动换行） */
static void get_actual_pos(int x, int y, int& actual_x, int& actual_y)
{
	int cols, lines, buf_cols, buf_lines;
	cct_getconsoleborder(cols, lines, buf_cols, buf_lines);

	actual_y = y + (x / buf_cols);
	actual_x = x % buf_cols;
}

/* 绘制单个菜单项 - 返回实际占用的行数 */
static int draw_menu_item(int x, int y, const char* item, int width, int bg, int fg, bool highlight)
{
	if (highlight)
		swap(bg, fg);

	int cols, lines, buf_cols, buf_lines;
	cct_getconsoleborder(cols, lines, buf_cols, buf_lines);

	cct_setcolor(bg, fg);
	cct_gotoxy(x, y);

	int drawn = 0;
	int i = 0;
	int start_y = y;
	int current_x = x;

	while (item[i] && drawn < width)
	{
		if (is_chinese((unsigned char)item[i], (unsigned char)item[i + 1]))
		{
			if (drawn + 2 <= width)
			{
				cout << item[i] << item[i + 1];
				drawn += 2;
				current_x += 2;
				i += 2;
			}
			else
			{
				cout << ' ';
				drawn++;
				current_x++;
				break;
			}
		}
		else
		{
			cout << item[i];
			drawn++;
			current_x++;
			i++;
		}
	}

	while (drawn < width)
	{
		cout << ' ';
		drawn++;
		current_x++;
	}

	// 计算实际占用的行数
	int end_x = x + width;
	int end_y = y + (end_x / buf_cols);

	return end_y - start_y + 1;
}

/* 重绘所有可见菜单项 */
static void redraw_all_items(const char menu[][MAX_ITEM_LEN], int x, int y_start, int display_high, int scroll_offset, int current_highlight, int width, int bg, int fg)
{
	for (int i = 0; i < display_high; ++i)
	{
		draw_menu_item(x, y_start + i, menu[scroll_offset + i], width, bg, fg, i == current_highlight);
	}
}

/* 检查鼠标是否在菜单项区域内 */
static int get_mouse_item(int MX, int MY, int start_x, int start_y, int width, int display_high)
{
	int cols, lines, buf_cols, buf_lines;
	cct_getconsoleborder(cols, lines, buf_cols, buf_lines);

	int content_y_start = start_y + 3;

	for (int i = 0; i < display_high; ++i)
	{
		int item_y = content_y_start + i;
		int item_x = start_x + 2;

		int actual_y = item_y + (item_x / buf_cols);
		int actual_x_start = item_x % buf_cols;
		int actual_x_end = actual_x_start + width;

		if (actual_x_end > buf_cols)
		{
			if (MY == actual_y)
			{
				if (MX >= actual_x_start)
					return i;
			}
			else if (MY == actual_y + 1)
			{
				if (MX < (actual_x_end % buf_cols))
					return i;
			}
		}
		else
		{
			if (MY == actual_y && MX >= actual_x_start && MX < actual_x_end)
				return i;
		}
	}

	return -1;
}

/* 弹出菜单主函数 */
int pop_menu(const char menu[][MAX_ITEM_LEN], const PopMenu* original_para)
{
	PopMenu para = *original_para;

	int item_count = count_menu_items(menu);
	if (item_count == 0)
		return 0;

	if (para.width % 2)
		para.width++;

	int title_width = get_display_width(para.title);
	int max_item_width = 0;
	for (int i = 0; i < item_count; ++i)
		max_item_width = max(max_item_width, get_display_width(menu[i]));

	para.width = max(para.width, max(title_width, max_item_width));
	if (para.width % 2)
		para.width++;

	int display_high = min(para.high, item_count);

	cct_setcursor(CCT_CURSOR_INVISIBLE);
	cct_enable_mouse();

	int x = para.start_x;
	int y = para.start_y;

	int cols, lines, buf_cols, buf_lines;
	cct_getconsoleborder(cols, lines, buf_cols, buf_lines);

	// 上边框
	cct_showstr(x, y, "┏", para.bg_color, para.fg_color, 1);
	cct_showstr(x + 2, y, "━", para.bg_color, para.fg_color, para.width / 2);

	int actual_x, actual_y;
	get_actual_pos(x + 2 + para.width, y, actual_x, actual_y);
	cct_showstr(actual_x, actual_y, "┓", para.bg_color, para.fg_color, 1);

	// 标题行
	y++;
	cct_showstr(x, y, "┃", para.bg_color, para.fg_color, 1);

	int left_space = (para.width - title_width) / 2;
	int right_space = para.width - title_width - left_space;

	cct_setcolor(para.bg_color, para.fg_color);
	cct_gotoxy(x + 2, y);
	for (int i = 0; i < left_space; ++i)
		cout << ' ';
	cout << para.title;
	for (int i = 0; i < right_space; ++i)
		cout << ' ';

	get_actual_pos(x + 2 + para.width, y, actual_x, actual_y);
	cct_showstr(actual_x, actual_y, "┃", para.bg_color, para.fg_color, 1);

	// 分隔线
	y++;
	cct_showstr(x, y, "┣", para.bg_color, para.fg_color, 1);
	cct_showstr(x + 2, y, "━", para.bg_color, para.fg_color, para.width / 2);
	get_actual_pos(x + 2 + para.width, y, actual_x, actual_y);
	cct_showstr(actual_x, actual_y, "┫", para.bg_color, para.fg_color, 1);

	// 内容区边框 - 关键修改：每一行都要计算右边框的实际位置
	int content_start_y = y + 1;
	for (int i = 0; i < display_high; ++i)
	{
		int row_y = content_start_y + i;

		// 左边框
		cct_showstr(x, row_y, "┃", para.bg_color, para.fg_color, 1);

		// 右边框 - 考虑内容可能换行
		int right_x = x + 2 + para.width;
		get_actual_pos(right_x, row_y, actual_x, actual_y);
		cct_showstr(actual_x, actual_y, "┃", para.bg_color, para.fg_color, 1);
	}

	// 下边框 - 也要考虑内容区可能的换行
	y = content_start_y + display_high;
	cct_showstr(x, y, "┗", para.bg_color, para.fg_color, 1);
	cct_showstr(x + 2, y, "━", para.bg_color, para.fg_color, para.width / 2);
	get_actual_pos(x + 2 + para.width, y, actual_x, actual_y);
	cct_showstr(actual_x, actual_y, "┛", para.bg_color, para.fg_color, 1);

	// 菜单交互
	int scroll_offset = 0;
	int current_highlight = 0;

	redraw_all_items(menu, x + 2, content_start_y, display_high, scroll_offset, current_highlight, para.width, para.bg_color, para.fg_color);

	int MX, MY, MAction, key1, key2;
	while (true)
	{
		int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);

		if (ret == CCT_KEYBOARD_EVENT)
		{
			if (key1 == 27)
				break;

			if (key1 == '\r')
				return scroll_offset + current_highlight + 1;

			if (key1 == 224)
			{
				if (key2 == KB_ARROW_UP)
				{
					if (current_highlight > 0)
						current_highlight--;
					else if (scroll_offset > 0)
						scroll_offset--;
				}
				else if (key2 == KB_ARROW_DOWN)
				{
					if (current_highlight < display_high - 1 && scroll_offset + current_highlight < item_count - 1)
						current_highlight++;
					else if (scroll_offset + display_high < item_count)
						scroll_offset++;
				}

				redraw_all_items(menu, x + 2, content_start_y, display_high, scroll_offset, current_highlight, para.width, para.bg_color, para.fg_color);
			}
		}
		else if (ret == CCT_MOUSE_EVENT)
		{
			int mouse_item = get_mouse_item(MX, MY, para.start_x, para.start_y, para.width, display_high);

			if (MAction == MOUSE_LEFT_BUTTON_CLICK && mouse_item >= 0)
			{
				return scroll_offset + mouse_item + 1;
			}
			else if (MAction == MOUSE_ONLY_MOVED && mouse_item >= 0)
			{
				if (mouse_item != current_highlight)
				{
					current_highlight = mouse_item;
					redraw_all_items(menu, x + 2, content_start_y, display_high, scroll_offset, current_highlight, para.width, para.bg_color, para.fg_color);
				}
			}
		}
	}

	cct_disable_mouse();
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
	return 0;
}