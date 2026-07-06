# API_SPEC.md

## ĐẶC TẢ TOÀN BỘ HÀM - HỆ THỐNG QUẢN LÝ NHÀ HÀNG

---

# MODULE 1 --------------------------------------------------------------------------------------------------------------------------------------------------------

## (Linked List & File)

---

## Task: khoiTaoDanhSach()

### Mục đích

Khởi tạo danh sách món ăn ban đầu.

### Input

* `Node **head`

### Output

* `head = NULL`

### Thuật toán

1. Gán `head` bằng `NULL`.

### Được phép

* Khởi tạo danh sách.

### Không được

* malloc
* free
* Đọc file
* Ghi file
* In menu

---

## Task: kiemTraTrungMa()

### Mục đích

Kiểm tra mã món đã tồn tại hay chưa.

### Input

* `Node *head`
* `char *maMon`

### Output

* `1`: Trùng mã
* `0`: Không trùng

### Thuật toán

1. Duyệt Linked List.
2. So sánh bằng `strcmp()`.
3. Nếu trùng trả về `1`.
4. Hết danh sách trả về `0`.

### Được phép

* Duyệt List.

### Không được

* Thêm Node.
* Xóa Node.
* Sửa Node.
* Ghi file.
* In menu.

---

## Task: themMonAn()

### Mục đích

Thêm một món ăn vào cuối Linked List.

### Input

* `Node **head`
* `MonAn monMoi`

### Output

* Linked List có thêm 1 Node.

### Thuật toán

1. malloc Node mới.
2. Gán dữ liệu.
3. Nếu List rỗng → head = node mới.
4. Nếu không → nối vào cuối List.

### Được phép

* malloc.
* Thao tác Linked List.

### Không được

* Kiểm tra trùng.
* Ghi file.
* Ghi History.
* Push Stack.
* Cập nhật BST.

---

## Task: hienThiDanhSach()

### Mục đích

Hiển thị toàn bộ menu.

### Input

* `Node *head`

### Output

* In bảng món ăn.

### Thuật toán

1. Duyệt List.
2. printf từng dòng.

### Không được

* Thay đổi dữ liệu.
* Xóa Node.
* Thêm Node.

---

## Task: xoaMonAn()

### Mục đích

Xóa món ăn khỏi Linked List.

### Input

* `Node **head`
* `char *maMon`

### Output

* Danh sách mất 1 Node.

### Thuật toán

1. Tìm Node.
2. Điều chỉnh liên kết.
3. free Node.

### Không được

* Push Stack.
* Ghi History.
* Cập nhật BST.
* Ghi File.

---

## Task: capNhatGiaTien()

### Mục đích

Đổi giá món ăn.

### Input

* `Node *head`
* `char *maMon`
* `int giaMoi`

### Output

* Giá món ăn được cập nhật.

### Thuật toán

1. Tìm Node.
2. Ghi đè giá mới.

### Không được

* Push Stack.
* Ghi History.
* Ghi File.
* Cập nhật BST.

---

## Task: docDuLieuTuFile()

### Mục đích

Đọc dữ liệu từ file.

### Input

* `Node **head`
* `tenFile`

### Output

* Linked List được tạo.

### Thuật toán

1. fopen("r")
2. Đọc từng dòng.
3. Tạo MonAn.
4. Gọi `themMonAn()`.

### Không được

* Ghi file.
* Gọi BST.
* Ghi History.

---

## Task: ghiDuLieuRaFile()

### Mục đích

Lưu toàn bộ danh sách xuống file.

### Input

* `Node *head`
* `tenFile`

### Output

* File được cập nhật.

### Thuật toán

1. fopen("w")
2. Duyệt List.
3. fprintf từng món.

### Không được

* Thay đổi dữ liệu.
* Push Stack.

---

## Task: giaiPhongDanhSach()

### Mục đích

Thu hồi bộ nhớ Linked List.

### Input

* `Node **head`

### Output

* `head = NULL`

### Thuật toán

1. while(head != NULL)
2. Lưu next.
3. free.
4. Sang Node tiếp.

---

# MODULE 2 --------------------------------------------------------------------------------------------------------------------------------------------------------

## (Stack, Queue, History)

---

## Task: pushUndo()

### Mục đích

Đưa thao tác vào Stack.

### Input

* `StackNode **top`
* `LoaiThaoTac`
* `MonAn`

### Output

* Stack tăng thêm 1 phần tử.

### Thuật toán

1. malloc.
2. Gán dữ liệu.
3. Chèn lên đỉnh Stack.

### Không được

* Undo.
* Gọi Linked List.
* Gọi BST.

---

## Task: popUndo()

### Mục đích

Lấy phần tử trên đỉnh Stack.

### Input

* `StackNode **top`

### Output

* Trả về dữ liệu Undo.

### Thuật toán

1. Kiểm tra rỗng.
2. Lưu dữ liệu.
3. Cập nhật top.
4. free.

### Không được

* Thêm món.
* Xóa món.
* Sửa món.
* Gọi BST.

---

## Task: enqueueOrder()

### Mục đích

Đưa món vào cuối Queue.

### Input

* `front`
* `rear`
* `MonAn`

### Output

* Queue tăng thêm 1 phần tử.

### Thuật toán

1. malloc.
2. Nếu Queue rỗng.
3. Nếu không nối cuối Queue.

### Không được

* Kiểm tra món.
* Tính doanh thu.
* Ghi History.

---

## Task: dequeueOrder()

### Mục đích

Lấy món đầu Queue.

### Input

* `front`
* `rear`

### Output

* Trả về món đầu tiên.

### Thuật toán

1. Lấy data.
2. Dời front.
3. free.

### Không được

* Cộng doanh thu.
* Ghi History.

---

## Task: ghiLichSuThaoTac()

### Mục đích

Ghi thao tác xuống history.txt.

### Input

* `hanhDong`
* `maMon`

### Output

* File có thêm 1 dòng.

### Thuật toán

1. fopen("a")
2. Lấy thời gian.
3. fprintf.

---

## Task: tinhTongDoanhThu()

### Mục đích

Tính tổng doanh thu.

### Input

* Queue đã phục vụ.

### Output

* Tổng tiền.

### Thuật toán

1. Duyệt Queue.
2. Cộng giá.

---

## Task: tinhGiaTrungBinhMenu()

### Mục đích

Tính giá trung bình thực đơn.

### Input

* Linked List.

### Output

* Giá trung bình.

### Thuật toán

1. Duyệt List.
2. Tính tổng.
3. Chia số món.

---

## Task: giaiPhongQueue()

### Mục đích

Giải phóng Queue.

### Thuật toán

Duyệt Queue và free từng Node.

---

## Task: giaiPhongStack()

### Mục đích

Giải phóng Stack.

### Thuật toán

Duyệt Stack và free từng Node.

---

# MODULE 3 --------------------------------------------------------------------------------------------------------------------------------------------------------

## (BST & Sorting)

---

## Task: themVaoCayBST()

### Mục đích

Thêm món vào BST.

### Input

* root
* MonAn

### Output

* Root mới.

### Thuật toán

1. Nếu root NULL → tạo TreeNode.
2. So sánh mã.
3. Rẽ trái hoặc phải.
4. Đệ quy.

### Không được

* Kiểm tra trùng.
* Ghi file.
* In menu.

---

## Task: timKiemTheoMaBST()

### Mục đích

Tìm kiếm theo mã.

### Input

* root
* maMon

### Output

* TreeNode*
* NULL nếu không tìm thấy.

### Thuật toán

So sánh mã và rẽ trái/phải theo BST.

### Không được

* In dữ liệu.
* Ghi file.

---

## Task: timKiemTheoTen()

### Mục đích

Tìm theo tên.

### Input

* Linked List.
* Tên.

### Output

* In các món phù hợp.

---

## Task: timKiemTheoKhoangGia()

### Mục đích

Tìm theo khoảng giá.

### Input

* List.
* Giá min.
* Giá max.

### Output

* In các món phù hợp.

---

## Task: sapXepTangTheoGia()

### Mục đích

Sắp xếp theo giá.

### Input

* Linked List.

### Output

* Danh sách đã sắp xếp.

### Thuật toán

Bubble Sort hoặc Interchange Sort.

---

## Task: sapXepTheoTen()

### Mục đích

Sắp xếp theo tên.

### Input

* Linked List.

### Output

* Danh sách đã sắp xếp.

### Thuật toán

So sánh bằng `strcmp()`.

---

## Task: duyetCayPreorder()

### Mục đích

In cây theo NLR.

---

## Task: duyetCayInorder()

### Mục đích

In cây theo LNR.

---

## Task: duyetCayPostorder()

### Mục đích

In cây theo LRN.

---

## Task: giaiPhongCay()

### Mục đích

Thu hồi bộ nhớ BST.

### Thuật toán

Duyệt hậu tự (Postorder) rồi `free()` từng TreeNode.
