# 🎯 Dijkstra Visualizer & CLI (DT079)

**Đồ án môn học Cấu trúc Dữ liệu và Giải thuật (INT13185)**  
Học viện Công nghệ Bưu chính Viễn thông (PTIT)  
Ứng dụng tìm đường đi ngắn nhất trên đồ thị vô hướng, kết hợp sức mạnh tính toán của C++ và khả năng trực quan hóa của Python.

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Python](https://img.shields.io/badge/Python-3.14-yellow.svg)](https://www.python.org/)
[![Pybind11](https://img.shields.io/badge/Pybind11-Binding-red.svg)](https://pybind11.readthedocs.io/)
[![CMake](https://img.shields.io/badge/CMake-3.10%2B-brightgreen.svg)](https://cmake.org/)
[![MSYS2](https://img.shields.io/badge/Environment-MSYS2%20UCRT64-orange.svg)](https://www.msys2.org/)

---

## 📖 Giới thiệu

Đồ án xây dựng giải thuật **Dijkstra** giải quyết bài toán tìm đường đi ngắn nhất từ một đỉnh nguồn đến đỉnh đích trên đồ thị vô hướng có trọng số không âm.

Dự án không chỉ dừng lại ở một chương trình Console (CLI) mà còn được thiết kế mở rộng:

1. **Lõi thuật toán C++** tối ưu hóa bằng Min-Heap và kỹ thuật Lazy Deletion.
2. **Thư viện Python (Pybind11)** cho phép tích hợp thuật toán C++ trực tiếp vào mã nguồn Python.
3. **Hệ thống Test & Visualizer** tự động hóa việc kiểm thử và vẽ đồ thị minh họa đường đi ngắn nhất.

---

## 🚀 Tính năng nổi bật

### 1. Thuật toán lõi (C++)
- **Dijkstra với Min-Heap**: Tối ưu hóa việc tìm đỉnh có khoảng cách nhỏ nhất với độ phức tạp `O((V + E) log V)`.
- **Kỹ thuật Lazy Deletion**: Loại bỏ các trạng thái lỗi thời trong hàng đợi ưu tiên mà không cần dùng `Decrease-Key` phức tạp.
- **Thống kê thực nghiệm (`Counters`)**: Đếm số lần `pops` (lấy khỏi Heap), `relaxations` (số cạnh xét), `updates` (số lần cập nhật thành công) giúp đánh giá hiệu năng thực tế.

### 2. Tích hợp đa nền tảng
- **CLI (Console)**: Nhận input qua `stdin`, in kết quả (mảng khoảng cách, đường đi, thống kê) ra `stdout`.
- **Python Module (`dijkstra_cpp`)**: Cung cấp hàm `run()` trả về dictionary chứa mảng khoảng cách, đường đi và tổng trọng số cho Python.

### 3. Kiểm thử tự động (Black-box Testing)
- Script `test_suite.py` tự động chạy **12 test cases** (từ cơ bản, biên, đến đồ thị phức tạp).
- So sánh kết quả thực tế từ `dijkstra.exe` với kết quả kỳ vọng.

### 4. Trực quan hóa đồ thị
- Script `visualize.py` sử dụng `NetworkX` và `Matplotlib`.
- Tự động phân tích output từ C++, vẽ đồ thị và **highlight màu đỏ** đường đi ngắn nhất tìm được.

---

## 🛠️ Công nghệ sử dụng

| Thành phần | Công nghệ |
|------------|-----------|
| **Ngôn ngữ lõi** | C++ 17 |
| **Binding** | Pybind11 |
| **Build System** | CMake |
| **Testing & Tool** | Python 3.11+, NetworkX, Matplotlib |
| **Môi trường (Khuyên dùng)** | MSYS2 UCRT64 (Windows) |

---

## 📂 Cấu trúc thư mục

```text
DijkstraProject/
├── bindings/
│   └── pybind_wrapper.cpp      # Cầu nối xuất module Python từ C++
├── src/
│   ├── dijkstra.h              # Khai báo cấu trúc dữ liệu và nguyên mẫu hàm
│   ├── dijkstra.cpp            # Cài đặt thuật toán Dijkstra, Relaxation, Trace
│   ├── main.cpp                # Chương trình CLI nhận input/stdout
│   ├── a_star.h                # (Mở rộng) Khai báo thuật toán A*
│   └── a_star.cpp              # (Mở rộng) Cài đặt thuật toán A*
├── scripts/
│   ├── test_suite.py           # Script chạy 12 ca kiểm thử tự động
│   └── visualize.py            # Script vẽ đồ thị trực quan bằng NetworkX
├── CMakeLists.txt              # File cấu hình build hệ thống
└── README.md                   # Tài liệu dự án
```

---

## ⚙️ Hướng dẫn cài đặt & Chạy (Dành cho MSYS2 UCRT64)

> ⚠️ **Lưu ý quan trọng**: Dự án được tối ưu để build trên Windows sử dụng **MSYS2 UCRT64**. Không khuyến khích dùng CMD/PowerShell mặc định vì dễ lỗi thiếu thư viện liên kết (linker).

### Bước 1: Cài đặt môi trường qua MSYS2 UCRT64
Mở terminal **MSYS2 UCRT64** (biểu tượng màu xanh lá trên Start Menu) và chạy các lệnh sau để cài đặt Toolchain, CMake, Python và Pybind11:

```bash
# Cập nhật hệ thống gói
pacman -Syu

# Cài đặt trình biên dịch C++, CMake và Python
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-python
pacman -S mingw-w64-ucrt-x86_64-python-pip

# Cài đặt Pybind11 (để CMake có thể tìm thấy)
pacman -S mingw-w64-ucrt-x86_64-pybind11
```

### Bước 2: Cài đặt thư viện Python cho Visualizer & Testing
Vẫn trong terminal MSYS2 UCRT64, di chuyển đến thư mục dự án và cài đặt thư viện:

```bash
pip install networkx matplotlib
```

### Bước 3: Build dự án với CMake
Tạo thư mục `build` và tiến hành biên dịch (lưu ý chỉ định Generator là `MinGW Makefiles`):

```bash
# 1. Tạo thư mục build và di chuyển vào trong
mkdir build
cd build

# 2. Cấu hình CMake (chỉ định rõ MinGW Makefiles)
cmake -G "MinGW Makefiles" ..

# 3. Build (sinh ra file dijkstra.exe và file thư viện .pyd)
cmake --build . -j
```
*(Sau bước này, bạn sẽ thấy file `dijkstra.exe` và file `dijkstra_cpp.cp314-mingw_x86_64.pyd` xuất hiện trong thư mục `build`).*

### Bước 4: Chạy chương trình

#### 🔹 Cách 1: Chạy CLI (Console)
```bash
# Vẫn đang ở trong thư mục build
./dijkstra.exe
```
*(Sau đó nhập dữ liệu test, ví dụ: `3 3` -> Enter -> `1 2 4`...)*

#### 🔹 Cách 2: Chạy Test Suite & Visualize tự động
**Quan trọng:** Để các script Python tìm thấy file `dijkstra.exe`, bạn hãy **copy file `dijkstra.exe` từ thư mục `build` vào nằm chung với thư mục `scripts/`**. 

Sau đó, di chuyển vào thư mục `scripts` và chạy:

```bash
# Di chuyển vào thư mục scripts
cd ../scripts

# Chạy kiểm thử tự động (12 ca)
python test_suite.py

# Chạy Visualize đồ thị
python visualize.py
```
*(Cửa sổ Matplotlib sẽ hiện lên, tắt cửa sổ này để xem ca tiếp theo).*

#### 🔹 Cách 3: Import module Python (Pybind11)
Tạo một file `test_pybind.py` nằm trong thư mục `build` và chạy:

```python
import dijkstra_cpp

edges = [(1, 2, 4), (1, 3, 1), (3, 2, 2)]
result = dijkstra_cpp.run(3, 1, 2, edges)
print("Khoảng cách:", result["dist"])
print("Đường đi:", result["path"])
print("Tổng trọng số:", result["total"])
```

---

## 📦 Hướng dẫn Đóng gói & Gửi cho máy khác (Không cần cài MSYS2)

Nếu bạn muốn nén dự án thành file ZIP gửi cho người khác chạy thử (máy họ không cài MSYS2), hãy chuẩn bị một thư mục **`Dijkstra_Release`** với cấu trúc như sau:

```text
Dijkstra_Release/
├── dijkstra.exe               <-- Copy từ build/ sang
├── libstdc++-6.dll            <-- Copy từ D:\msys64\ucrt64\bin
├── libgcc_s_seh-1.dll         <-- Copy từ D:\msys64\ucrt64\bin
├── libwinpthread-1.dll        <-- Copy từ D:\msys64\ucrt64\bin
├── test_suite.py              <-- Copy từ scripts/ sang
└── visualize.py               <-- Copy từ scripts/ sang
```

**Hướng dẫn cho người nhận:**
1. Máy cần cài sẵn Python 3.
2. Mở CMD/Terminal tại thư mục vừa giải nén và chạy:
   ```bash
   pip install networkx matplotlib
   python test_suite.py
   python visualize.py
   ```

---

## ⚠️ Giới hạn & Lưu ý kỹ thuật

- **Số đỉnh `n` tối đa = 50**: Giới hạn này được đặt ở `main.cpp` để đảm bảo thời gian chạy và in kết quả ra màn hình console không bị quá tải.
- **Không hỗ trợ trọng số âm**: Thuật toán Dijkstra không hoạt động đúng với cạnh âm. Chương trình có bộ lọc kiểm tra `hasNegativeWeight` và sẽ chặn ngay từ đầu.
- **Kỹ thuật Lazy Deletion**: Hàng đợi ưu tiên (Min-Heap) có thể chứa tới `O(E)` phần tử lỗi thời. Điều này là bình thường và không ảnh hưởng đến tính đúng đắn của thuật toán.