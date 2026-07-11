# 🍽️ Restaurant Manager
 
> Hệ thống quản lý nhà hàng được xây dựng bằng ngôn ngữ **C**, mô phỏng quy trình quản lý thực đơn, đặt món và lưu trữ dữ liệu bằng các cấu trúc dữ liệu cơ bản và nâng cao.

---

## 📌 Thông tin dự án

| Thuộc tính | Nội dung |
|------------|----------|
| Ngôn ngữ | C |
| Môn học | Cấu trúc dữ liệu & Giải thuật |
| Nhóm | Nhóm 6 |

---

# 🎯 Mục tiêu

Xây dựng chương trình **Console Application** mô phỏng hoạt động quản lý của một nhà hàng.

Hệ thống hỗ trợ:

- Quản lý thực đơn
- Quản lý đặt món
- Lưu và đọc dữ liệu từ file
- Ghi lịch sử thao tác
- Ứng dụng các cấu trúc dữ liệu:
  - Danh sách liên kết (Linked List)
  - Ngăn xếp (Stack)
  - Hàng đợi (Queue)
  - Cây nhị phân tìm kiếm (BST)

---

# ✨ Chức năng chính

## 📋 Quản lý thực đơn (CRUD)

| Chức năng | Mô tả |
|-----------|------|
| ➕ Thêm món | Thêm món mới, kiểm tra trùng mã trước khi lưu |
| 📄 Hiển thị | In danh sách món theo dạng bảng |
| 🔍 Tìm kiếm | Theo mã, tên hoặc khoảng giá |
| ✏️ Cập nhật | Sửa tên hoặc giá món ăn |
| ❌ Xóa | Xóa món theo mã hoặc tên |
| ↕️ Sắp xếp | Theo tên hoặc giá (tăng/giảm) |
| 💾 File | Tự động lưu và đọc dữ liệu từ `restaurant.txt` |

---

# 🚀 Ứng dụng Cấu trúc Dữ liệu

## 📚 Stack (Undo)

Lưu lịch sử các thao tác:

- Thêm món
- Xóa món
- Sửa món

Khi người dùng chọn **Undo**, chương trình lấy dữ liệu từ đỉnh Stack để khôi phục trạng thái trước đó.

---

## 📥 Queue (Đặt món)

Mô phỏng quá trình phục vụ trong nhà hàng.

- Khách gọi món → Thêm vào Queue
- Bếp chế biến → Lấy món đầu Queue

Áp dụng nguyên tắc:

> **FIFO (First In - First Out)**

---

## 🌳 Binary Search Tree (BST)

Đưa **Mã món ăn** vào cây BST nhằm tăng tốc độ tìm kiếm.

Hỗ trợ:

- Preorder
- Inorder
- Postorder

---

# 📊 Thống kê

Hệ thống hỗ trợ:

- Tổng doanh thu
- Giá trung bình của thực đơn
- Số lượng món ăn

Đồng thời ghi toàn bộ thao tác vào file:

```text
history.txt
```

Ví dụ:

```text
[10:15] ADD    MON001
[10:17] UPDATE MON002
[10:20] DELETE MON005
```

---

# 🗂 Cấu trúc dữ liệu chính

Toàn bộ hệ thống (CRUD, Stack, Queue, BST) đều thao tác trên một đối tượng chung là **Món ăn**.

```c
typedef struct
{
    char maMon[20];
    char tenMon[50];
    int giaTien;
} MonAn;
```

Định nghĩa tại:

```text
restaurant.h
```

---

# 📁 Dữ liệu

| File | Chức năng |
|------|-----------|
| restaurant.txt | Lưu danh sách món ăn |
| history.txt | Lưu lịch sử thao tác |

---

# 🛠 Công nghệ sử dụng

- Ngôn ngữ C
- Linked List
- Stack
- Queue
- Binary Search Tree (BST)
- File Handling

---

# 👥 Nhóm thực hiện

**Nhóm 6**
