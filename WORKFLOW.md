# WORKFLOW TỔNG THỂ HỆ THỐNG QUẢN LÝ NHÀ HÀNG

Tài liệu này mô tả toàn bộ luồng hoạt động của chương trình từ khi khởi động đến khi kết thúc. Mục đích là để các thành viên trong nhóm hiểu dữ liệu sẽ đi như thế nào và khi nào phần code của mình được sử dụng.

---

# GIAI ĐOẠN 1: KHỞI ĐỘNG HỆ THỐNG

## Mục tiêu

Đưa toàn bộ dữ liệu từ file lên bộ nhớ để chương trình sẵn sàng hoạt động.

### Bước 1: Khởi động chương trình

Khi chạy chương trình, hệ thống tạo các cấu trúc dữ liệu cần thiết:

* Linked List (Quản lý danh sách món ăn)
* Queue (Quản lý khách đặt món)
* Stack (Lưu thao tác Undo)
* BST (Tìm kiếm nhanh)

Ban đầu tất cả đều rỗng.

---

### Bước 2: Đọc dữ liệu từ File

Hệ thống mở file `restaurant.txt`.

Nếu file có dữ liệu, chương trình sẽ đọc từng dòng và tạo thành các món ăn trong Linked List.

Ví dụ:

``` 
M01 Pho 50000
M02 ComTam 45000
M03 BunBo 55000
```

Sau khi đọc xong:

``` 
M01
 │
 ▼
M02
 │
 ▼
M03
```

---

### Bước 3: Xây dựng BST

Sau khi Linked List hoàn tất, hệ thống duyệt toàn bộ danh sách để tạo BST.

BST chỉ dùng để tăng tốc tìm kiếm theo **Mã món**.

Ví dụ:

``` 
        M02
       /   \
     M01   M03
```

---

### Bước 4: Hiển thị Menu

Sau khi dữ liệu đã sẵn sàng, Menu chính xuất hiện.

Người dùng bắt đầu sử dụng chương trình.

---

# GIAI ĐOẠN 2: QUẢN LÝ THỰC ĐƠN

## 1. Thêm món ăn

Người dùng chọn chức năng **Thêm món**.

Hệ thống thực hiện:

1. Nhập Mã món, Tên món và Giá.
2. Kiểm tra Mã món đã tồn tại hay chưa.
3. Nếu trùng mã → Thông báo lỗi.
4. Nếu không trùng:

   * Thêm món vào Linked List.
   * Lưu thao tác vào Stack (phục vụ Undo).
   * Cập nhật BST.
   * Ghi lịch sử vào `history.txt`.
5. Thông báo **Thêm thành công**.

---

## 2. Hiển thị danh sách

Người dùng chọn **Hiển thị**.

Hệ thống duyệt toàn bộ Linked List và in ra bảng thực đơn.

Ví dụ:

``` 
+------+------------+---------+
| Mã   | Tên món    | Giá     |
+------+------------+---------+
| M01  | Phở        | 50000   |
| M02  | Cơm Tấm    | 45000   |
| M03  | Bún Bò     | 55000   |
+------+------------+---------+
```

---

## 3. Tìm kiếm

Người dùng có thể tìm theo:

### Theo Mã

* Tìm trên BST.
* Nếu có → Hiển thị thông tin.
* Nếu không → Báo không tìm thấy.

### Theo Tên

* Duyệt Linked List.
* Hiển thị tất cả món phù hợp.

### Theo Khoảng Giá

Ví dụ:

``` 
30000 → 60000
```

Hệ thống hiển thị tất cả món nằm trong khoảng giá đó.

---

## 4. Cập nhật giá

Người dùng nhập Mã món.

Sau đó nhập Giá mới.

Hệ thống sẽ:

1. Tìm món ăn.
2. Lưu dữ liệu cũ vào Stack.
3. Cập nhật giá mới.
4. Đồng bộ lại BST.
5. Ghi lịch sử thao tác.
6. Thông báo thành công.

---

## 5. Xóa món

Người dùng nhập Mã món.

Hệ thống:

1. Kiểm tra món có tồn tại.
2. Lưu thông tin món vào Stack.
3. Xóa khỏi Linked List.
4. Đồng bộ lại BST.
5. Ghi lịch sử thao tác.
6. Thông báo xóa thành công.

---

## 6. Sắp xếp

Người dùng có thể chọn:

* Sắp xếp theo Giá.
* Sắp xếp theo Tên.

Sau khi sắp xếp xong, hệ thống hiển thị lại danh sách mới.

---

# GIAI ĐOẠN 3: QUẢN LÝ ĐẶT MÓN (QUEUE)

Queue hoạt động theo nguyên tắc **FIFO (First In - First Out)**.

## Khách gọi món

Ví dụ:

Khách 1 gọi:

``` 
M01
```

Queue:

``` 
M01
```

Khách 2 gọi:

``` 
M02
```

Queue:

``` 
M01
 │
 ▼
M02
```

Khách 3 gọi:

``` 
M04
```

Queue:

``` 
M01
 │
 ▼
M02
 │
 ▼
M04
```

Khách gọi trước sẽ được phục vụ trước.

---

## Bếp phục vụ

Khi bếp hoàn thành món đầu tiên:

Queue:

``` 
M01
 │
 ▼
M02
 │
 ▼
M04
```

Sau khi phục vụ:

``` 
M02
 │
 ▼
M04
```

Đồng thời hệ thống:

* Cộng doanh thu.
* Ghi lịch sử phục vụ.

---

# GIAI ĐOẠN 4: HOÀN TÁC (UNDO)

Stack hoạt động theo nguyên tắc **LIFO (Last In - First Out)**.

Mỗi khi:

* Thêm món.
* Xóa món.
* Cập nhật giá.

Hệ thống sẽ lưu thông tin cũ vào Stack.

Ví dụ:

Người dùng xóa món:

``` 
M03
```

Stack:

``` 
TOP
 │
 ▼
XOA - M03
```

Nếu người dùng chọn **Undo**:

Hệ thống sẽ:

1. Lấy dữ liệu trên đỉnh Stack.
2. Khôi phục món ăn về trạng thái trước đó.
3. Đồng bộ lại BST.
4. Ghi lịch sử hoàn tác.

Kết quả:

M03 xuất hiện lại trong danh sách.

---

# GIAI ĐOẠN 5: THỐNG KÊ

Người dùng chọn **Thống kê**.

Hệ thống tính:

* Tổng doanh thu.
* Giá trung bình của toàn bộ thực đơn.

Sau đó hiển thị kết quả ra màn hình.

---

# GIAI ĐOẠN 6: THOÁT CHƯƠNG TRÌNH

Khi người dùng chọn **Thoát**.

Hệ thống thực hiện theo thứ tự:

### Bước 1

Lưu toàn bộ Linked List xuống file:

``` 
restaurant.txt
```

---

### Bước 2

Giải phóng toàn bộ bộ nhớ:

* Linked List
* Queue
* Stack
* BST

---

### Bước 3

Kết thúc chương trình.

---

# TÓM TẮT LUỒNG HOẠT ĐỘNG

``` 
Mở chương trình
      │
      ▼
Đọc dữ liệu từ restaurant.txt
      │
      ▼
Tạo Linked List
      │
      ▼
Xây dựng BST
      │
      ▼
Hiển thị Menu
      │
      ├── Thêm món
      ├── Hiển thị danh sách
      ├── Tìm kiếm
      ├── Cập nhật giá
      ├── Xóa món
      ├── Sắp xếp
      ├── Đặt món (Queue)
      ├── Phục vụ món (Queue)
      ├── Undo (Stack)
      ├── Thống kê
      └── Thoát
              │
              ▼
      Lưu dữ liệu xuống File
              │
              ▼
      Giải phóng bộ nhớ
              │
              ▼
      Kết thúc chương trình
```

---

# PHÂN CÔNG THÀNH VIÊN

## A

* Quản lý Linked List.
* Thêm, sửa, xóa, hiển thị món ăn.
* Đọc/Ghi dữ liệu từ file.

## B

* Quản lý Stack (Undo).
* Quản lý Queue (Đặt món).
* Ghi lịch sử thao tác.
* Thống kê doanh thu và giá trung bình.

## C

* Xây dựng và quản lý BST.
* Tìm kiếm theo Mã món.
* Tìm kiếm theo Tên và Khoảng giá.
* Sắp xếp danh sách.

## Leader

* Thiết kế cấu trúc dự án.
* Thiết kế `restaurant.h`.
* Xây dựng Menu (`main.c`).
* Điều phối luồng chương trình.
* Ghép code của các thành viên.
* Kiểm thử và sửa lỗi khi tích hợp.

