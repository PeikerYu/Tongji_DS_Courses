def solve_coloring(graph, colors):
    num_provinces = len(graph)
    provinces = list(graph.keys())
    coloring = {}
    def is_safe(province, color):
        for neighbor in graph[province]:
            if neighbor in coloring and coloring[neighbor] == color:
                return False
        return True
    def backtrack(k):
        if k == num_provinces:
            return True
        current_province = provinces[k]
        for color in colors:
            if is_safe(current_province, color):
                coloring[current_province] = color
                if backtrack(k + 1):
                    return True
                del coloring[current_province]
        return False
    if backtrack(0):
        return coloring
    else:
        return None
m_list = {
    '河北': ['内蒙古', '辽宁', '山东', '河南', '山西', '陕西'],
    '山西': ['河北', '河南', '陕西', '内蒙古'],
    '内蒙古': ['黑龙江', '吉林', '辽宁', '河北', '山西', '陕西', '宁夏', '甘肃'],
    '辽宁': ['内蒙古', '河北', '吉林'],
    '吉林': ['黑龙江', '内蒙古', '辽宁'],
    '黑龙江': ['内蒙古', '吉林'],
    '山东': ['河北', '河南', '安徽', '江苏'],
    '河南': ['河北', '山东', '安徽', '湖北', '陕西', '山西'],
    '安徽': ['山东', '河南', '湖北', '江西', '江苏', '浙江'],
    '江苏': ['山东', '安徽', '浙江'],
    '浙江': ['江苏', '安徽', '江西', '福建'],
    '福建': ['浙江', '江西', '广东'],
    '广东': ['福建', '江西', '湖南', '广西'],
    '广西': ['广东', '湖南', '贵州', '云南'],
    '云南': ['广西', '贵州', '四川', '西藏'],
    '西藏': ['新疆', '青海', '四川', '云南'],
    '四川': ['陕西', '甘肃', '青海', '西藏', '云南', '贵州'],
    '贵州': ['四川', '云南', '广西', '湖南'],
    '湖南': ['湖北', '贵州', '广西', '广东', '江西'],
    '湖北': ['河南', '陕西', '湖南', '江西', '安徽'],
    '江西': ['安徽', '湖北', '湖南', '广东', '福建', '浙江'],
    '陕西': ['山西', '河南', '湖北', '四川', '甘肃', '宁夏', '河北', '内蒙古'],
    '甘肃': ['新疆', '内蒙古', '宁夏', '陕西', '四川', '青海'],
    '青海': ['新疆', '甘肃', '四川', '西藏'],
    '宁夏': ['内蒙古', '陕西', '甘肃'],
    '新疆': ['西藏', '青海', '甘肃'],
}
colors = ['红', '黄', '蓝', '绿']
solution = solve_coloring(m_list, colors)
if solution:
    print("找到一种四色着色方案：")
    sorted_solution = sorted(solution.items())
    for province, color in sorted_solution:
        print(f"{province}: {color}")
else:
    print("未能找到四色着色方案。")