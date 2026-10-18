import pandas as pd
file_path = 'st2025.xlsx'
shedule_df = pd.read_excel(file_path, sheet_name='shedule', dtype={"学号": str})
info_df = pd.read_excel(file_path, sheet_name='info', dtype={"学号": str})
xueke_df = pd.read_excel(file_path, sheet_name='xueke', dtype={"学号": str})

s_id=input("请输入要查询的学号：")
s_dict={}
s_dict["学号"]=s_id
student_info = info_df[info_df["学号"] == s_id]
s_dict["姓名"]=student_info.iloc[0]["姓名"]
s_dict["英文姓名"]=student_info.iloc[0]["英文姓名"]
s_dict["性别"]=student_info.iloc[0]["性别"]
course_list=s_dict["选课冲突"]=[]
s_row = xueke_df[xueke_df["学号"] == s_id]
for index, row in shedule_df.iterrows():
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
            if len(subjects_for_cell)>=2:
                sub_dict = {}
                sub_dict["上课时间"] = row["上课时间"]
                sub_dict["日期"] = column_name
                sub_dict["冲突课程"]=",".join(subjects_for_cell)
                course_list.append(sub_dict)
print(s_dict)




