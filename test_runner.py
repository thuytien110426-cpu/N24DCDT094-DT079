import subprocess

test_cases = [
    ("A01", "3 3\n1 2 4\n1 3 1\n3 2 2\n1 2\n", "d=[0, 3, 1]; duong=[1, 3, 2]; tong=3"),
    ("A02", "3 1\n1 2 5\n1 3\n", "d=[0, 5, INF]; KHONG CO DUONG"),
    # Sửa A03: Expected phải tính từ đỉnh nguồn s=2
    ("A03", "5 4\n1 2 10\n1 3 5\n1 4 8\n1 5 2\n2 5\n", "d=[10, 0, 15, 18, 12]; duong=[2, 1, 5]; tong=12"),
    ("A04", "4 4\n1 2 2\n2 3 2\n3 4 2\n4 1 10\n1 4\n", "d=[0, 2, 4, 6]; duong=[1, 2, 3, 4]; tong=6"),
    ("A05", "3 2\n1 2 5\n2 3 6\n2 2\n", "d=[5, 0, 6]; duong=[2]; tong=0"),
    ("A06", "3 3\n1 2 0\n2 3 0\n1 3 5\n1 3\n", "d=[0, 0, 0]; duong=[1, 2, 3]; tong=0"),
    ("A07", "1 0\n1 1\n", "d=[0]; duong=[1]; tong=0"),
    ("A08", "3 2\n1 2 -5\n2 3 4\n1 3\n", "LOI: Do thi chua canh co trong so am. Dijkstra khong the chay."),
    ("KT09", "2 1\n1 2 10\n1 2\n", "d=[0, 10]; duong=[1, 2]; tong=10"),
    ("KT10", "4 3\n1 2 1\n2 3 1\n3 4 1\n1 4\n", "d=[0, 1, 2, 3]; duong=[1, 2, 3, 4]; tong=3"),
    # Sửa KT11: 1 -> 3 -> 2 ngắn hơn 1 -> 2 (50 + 1 = 51 < 100)
    ("KT11", "3 3\n1 2 100\n2 3 1\n1 3 50\n1 3\n", "d=[0, 51, 50]; duong=[1, 3]; tong=50"),
    ("KT12", "4 5\n1 2 1\n1 3 5\n2 3 1\n2 4 5\n3 4 1\n1 4\n", "d=[0, 1, 2, 3]; duong=[1, 2, 3, 4]; tong=3")
]

pass_count = 0
print(f"{'Mã ca':<6} | {'Trạng thái':<10} | {'Ghi chú'}")
print("-" * 40)

for case_id, inp, expected in test_cases:
    process = subprocess.run(['./dijkstra'], input=inp, text=True, capture_output=True)
    actual = process.stdout.strip()
    
    # CHUẨN HÓA CHUỖI: Xóa mọi dấu xuống dòng và khoảng trắng thừa để so sánh chính xác
    expected_clean = " ".join(expected.split())
    actual_clean = " ".join(actual.split())
    
    if expected_clean == actual_clean: 
        print(f"{case_id:<6} | {'PASS':<10} | OK")
        pass_count += 1
    else:
        print(f"{case_id:<6} | {'FAIL':<10} | Cần kiểm tra lại")
        print(f"  -> Expected: {expected_clean}")
        print(f"  -> Actual:   {actual_clean}")

print("-" * 40)
print(f"TỔNG KẾT: {pass_count}/{len(test_cases)} CA PASS")