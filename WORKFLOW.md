<div align="center">
  <h1>🚀 BẢN ĐỒ LUỒNG HOẠT ĐỘNG (WORKFLOW)</h1>
  <p><b>Hệ Thống Quản Lý Nhà Hàng - Nhóm 5</b></p>
  
  [![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
  [![Architecture](https://img.shields.io/badge/Architecture-Event%20Loop-orange.svg)]()
  [![Status](https://img.shields.io/badge/Status-Completed-success.svg)]()
</div>

---

> **💡 Kiến trúc cốt lõi:** Phần mềm được thiết kế theo mô hình **Vòng lặp sự kiện (Event Loop)** kết hợp với cơ chế **Định tuyến (Router)** để điều hướng xử lý luồng dữ liệu (Data Flow) giữa các Module một cách mượt mà, tốc độ cao và tuyệt đối không rò rỉ bộ nhớ.

## 🟢 GIAI ĐOẠN 1: KHỞI ĐỘNG HỆ THỐNG (BOOTING)
*Tiến trình chạy ngầm ngay khi khởi chạy file `QuanLyNhaHang.exe`, trước khi giao diện UI xuất hiện.*

| Bước | Hành động | Mô tả chi tiết |
| :---: | :--- | :--- |
| 1️⃣ | **Khởi tạo trạng thái gốc** | Khai báo 7 con trỏ quản lý (`menuHead`, `bstRoot`, `undoTop`...) và gán `NULL` để chống lỗi con trỏ hoang. |
| 2️⃣ | **Auto-Load (Khôi phục)** | Đọc dữ liệu từ file vật lý `data/restaurant.txt` và nạp vào **Singly Linked List**. |
| 3️⃣ | **Đồng bộ hóa (Initial Sync)** | Duyệt List một lần để đẩy toàn bộ dữ liệu sang **Cây BST**, chuẩn bị cho tìm kiếm siêu tốc. |
| 4️⃣ | **Ghi Log hệ thống** | Thêm dòng nhật ký vào **Doubly Linked List**: *"Hệ thống khởi động thành công"*. |

<br>

## 🟡 GIAI ĐOẠN 2: VÒNG LẶP ĐIỀU HƯỚNG (EVENT LOOP)
*Hệ thống duy trì trạng thái hoạt động liên tục qua vòng lặp `while(1)`.*

- **🖥️ Hiển thị giao diện:** In bảng Menu chính gồm 11 chức năng.
- **🛡️ Tấm khiên bảo vệ (Input Shield):**
  - Chờ người dùng nhập phím lựa chọn.
  - ⚠️ **Bẫy lỗi:** Nếu nhập sai kiểu dữ liệu (nhập chữ thay vì số), hàm `xoaBoNhoDem()` sẽ kích hoạt để dọn sạch rác trong RAM, ngăn chặn lỗi trôi lệnh (Crash).
- **🔀 Định tuyến xử lý:** Dựa trên số đã chọn, trình `switch-case` gọi các hàm Giao diện (`ui...`) tương ứng để bắt đầu xử lý nghiệp vụ.

<br>

## 🔵 GIAI ĐOẠN 3: XỬ LÝ NGHIỆP VỤ CỐT LÕI (CORE LOGIC)
*Sự phối hợp nhịp nhàng giữa 5 cấu trúc dữ liệu khi có thay đổi xảy ra. (Bấm vào từng luồng bên dưới để xem chi tiết):*

<details>
<summary><b>📌 Luồng 1: Thêm / Xóa / Sửa món (Đồng bộ CRUD)</b></summary>
<br>

*Sự phối hợp thời gian thực của cả 3 thành viên:*
1. **Validate:** Kiểm tra trùng mã món trên List *(Phát)*.
2. **Update:** Cập nhật dữ liệu vật lý vào **Linked List** *(Phát)*.
3. **Sync:** Cập nhật nút tương ứng trên **Cây BST** *(Hoàng)*.
4. **Backup:** Đóng gói thông tin cũ đẩy vào đỉnh **Stack** để sẵn sàng Hoàn tác *(Lê)*.
5. **Trace:** Ghi nhận hành động vào **Doubly Linked List** để truy vết *(Lê)*.
</details>

<details>
<summary><b>👨‍🍳 Luồng 2: Phục vụ nhà bếp (Queue)</b></summary>
<br>

- 📥 **Order (Enqueue):** Khách gọi món ➔ Đẩy vào đuôi hàng đợi.
- 📤 **Serve (Dequeue):** Bếp làm xong ➔ Lấy từ đầu hàng đợi ra phục vụ. Tuân thủ nghiêm ngặt nguyên tắc **FIFO (First In - First Out)**.
</details>

<details>
<summary><b>⏪ Luồng 3: Cỗ máy thời gian Hoàn tác (Stack)</b></summary>
<br>

- Quản lý bấm phím `8` ➔ Hệ thống kiểm tra **Stack**.
- Lấy thao tác gần nhất ở Đỉnh (**LIFO**) và thực hiện hành động đảo ngược.
- Khôi phục dữ liệu gốc ngay lập tức với tốc độ **O(1)**.
</details>

<details>
<summary><b>🔍 Luồng 4: Tìm kiếm siêu tốc (BST)</b></summary>
<br>

- Hệ thống bỏ qua việc duyệt tuần tự mất thời gian của Linked List.
- Chui thẳng vào **Cây nhị phân tìm kiếm (BST)**.
- So sánh và rẽ nhánh liên tục, tìm ra món ăn với độ phức tạp **O(log n)**.
</details>

<br>

## 🔴 GIAI ĐOẠN 4: THOÁT HỆ THỐNG AN TOÀN (SHUTDOWN)
*Kịch bản kích hoạt khi người dùng chọn phím `0`.*

- [x] **Auto-Save (Bảo vệ dữ liệu):** Tự động ghi đè an toàn toàn bộ dữ liệu từ RAM xuống file vật lý `restaurant.txt` trước khi tắt.
- [x] **Memory Cleanup (Giải phóng RAM):** Hệ thống "Xe rác" duyệt qua toàn bộ các cấu trúc dữ liệu (List, Cây, Stack, Queue) và gọi hàm `free()` cho từng Node.
- [x] **Kết thúc tiến trình:** Trình điều hành trả về `return 0;`, hoàn trả 100% bộ nhớ cho máy tính, triệt tiêu hoàn toàn Memory Leak.

---
<div align="center">
  <i>Đồ án Cấu Trúc Dữ Liệu & Thuật Toán - Thực hiện bởi Nhóm 5</i>
</div>