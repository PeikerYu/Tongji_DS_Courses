import pandas as pd
file_path = 'st2025.xlsx'
shedule_df = pd.read_excel(file_path, sheet_name='shedule', dtype={"学号": str})
info_df = pd.read_excel(file_path, sheet_name='info', dtype={"学号": str})
xueke_df = pd.read_excel(file_path, sheet_name='xueke', dtype={"学号": str})

def query_name(student_id):
    student_info = info_df[info_df['学号'] == student_id]
    if not student_info.empty:
        student_name = student_info.iloc[0]['姓名']
        return student_name
    return "未知学生"

def get_chinese_display_width(text):
    return sum(2 if '\u4e00' <= char <= '\u9fff' else 1 for char in text)


def center_text(text, total_width):
    display_width = get_chinese_display_width(text)
    padding = total_width - display_width
    left_padding = padding // 2
    right_padding = padding - left_padding
    return ' ' * left_padding + text + ' ' * right_padding

def left_align_chinese_text(text, column_width):
    chinese_len = sum(2 if '\u4e00' <= char <= '\u9fff' else 1 for char in text)
    padding = column_width - chinese_len
    if padding < 0:
        padding = 0
    return text + ' ' * padding

student_id = input("请输入要查询的学号：")
student_name = query_name(student_id)
if student_name == "未知学生":
    print(f"学号 {student_id} 未找到，请检查输入。")
else:
    col_width = 20
    total_width = col_width * 6
    header_list = ["上课时间", "周一", "周二", "周三", "周四", "周五"]
    print(center_text(f"{student_name}的课表", total_width))
    print("*" * total_width)
    for header in header_list:
        print(left_align_chinese_text(header, col_width), end="")
    print()
    s_row = xueke_df[xueke_df["学号"] == student_id]
    for index, row in shedule_df.iterrows():
        print(left_align_chinese_text(row["上课时间"], col_width), end="")
        for column_name in ["周一", "周二", "周三", "周四", "周五"]:
            cell_value = row[column_name]
            subjects_for_cell = []
            if pd.notna(cell_value) and isinstance(cell_value, str):
                scheduled_subjects = cell_value.split(",")
                for s_column in xueke_df.columns:
                    if s_column == "学号":
                        continue
                    student_takes_subject = False
                    if s_column in s_row.columns and not s_row.empty:
                        s_cell_value = s_row[s_column].values[0]
                        if s_cell_value == "√":
                            student_takes_subject = True
                    if student_takes_subject and s_column in scheduled_subjects:
                        subjects_for_cell.append(s_column)
            print(left_align_chinese_text(",".join(subjects_for_cell), col_width), end="")
        print()