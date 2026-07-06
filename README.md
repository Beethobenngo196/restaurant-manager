QuanLyNhaHang_Nhom6/
│
├── bin/                  # Chứa file thực thi (.exe) sau khi biên dịch
├── src/                  # Chứa các file mã nguồn C
│   ├── main.c            # Hàm main chứa Menu tổng
│   ├── phat.c            # Code xử lý List & File
│   ├── trung.c           # Code xử lý Stack, Queue, Lịch sử
│   └── long.c            # Code xử lý BST, Sắp xếp
│
├── include/              # Chứa các file thư viện tự định nghĩa
│   └── restaurant.h      # File định nghĩa Struct và khai báo hàm chung
│
├── data/                 # Chứa các file text lưu trữ dữ liệu
│   ├── restaurant.txt    # Data món ăn/hóa đơn
│   └── history.txt       # Data lịch sử thao tác
│
└── README.md


DỰ ÁN: HỆ THỐNG QUẢN LÝ NHÀ HÀNG 
Ngôn ngữ: C
Nhóm thực hiện: Nhóm 6

I. MỤC TIÊU DỰ ÁN
Xây dựng một chương trình console mô phỏng hoạt động vận hành của một nhà hàng, bao gồm việc quản lý thực đơn, đặt món và lưu vết hoạt động. Hệ thống yêu cầu tích hợp các cấu trúc dữ liệu cơ bản (Danh sách) và nâng cao (Stack, Queue, BST).

II. YÊU CẦU CHỨC NĂNG CỐT LÕI (CRUD)
Phần này đảm bảo dữ liệu nền tảng cho toàn bộ hệ thống:

Thêm & Nhập liệu: Nhập thông tin món ăn (Mã, Tên, Giá, Loại). Bắt buộc phải có thuật toán kiểm tra trùng Mã món ăn trước khi lưu.

Hiển thị: In danh sách món ăn ra console dưới định dạng bảng chuẩn xác.

Tìm kiếm: Hỗ trợ tìm kiếm thông tin theo Mã món, Tên món, hoặc Khoảng giá.

Xóa & Sửa: Cho phép cập nhật giá tiền hoặc xóa món ăn khỏi thực đơn theo Mã hoặc Tên.

Sắp xếp: Sắp xếp danh sách tăng/giảm dựa trên Giá tiền hoặc Tên món.

Quản lý File: Toàn bộ dữ liệu phải được lưu xuống file text và tự động load lên khi khởi động chương trình.

III. YÊU CẦU TÍCH HỢP DSA NÂNG CAO
Phần này mô phỏng các nghiệp vụ thực tế của nhà hàng:

Tính năng Hoàn tác (Dùng Stack): Lưu lại trạng thái của các lệnh Thêm/Xóa/Sửa. Khi gọi hàm Undo (Lấy từ đỉnh Stack), hệ thống phải phục hồi lại trạng thái trước đó.

Quản lý luồng Đặt món (Dùng Queue): Khách hàng gọi món sẽ được đưa vào Hàng đợi. Bếp sẽ xử lý trả món theo nguyên tắc FIFO (Vào trước, phục vụ trước).

Truy xuất tốc độ cao (Dùng Cây BST): Đưa dữ liệu Mã món ăn vào Cây nhị phân tìm kiếm để tối ưu hóa thời gian tìm kiếm. Hỗ trợ in dữ liệu theo 3 phép duyệt cây (Preorder, Inorder, Postorder).

Thống kê & Ghi Log: Tính tổng doanh thu bán hàng và tính giá trị trung bình của thực đơn. Ghi vết mọi thao tác thay đổi dữ liệu (Ví dụ: Thêm MON001) vào file history.txt.


                                                       General data
Mọi tính năng từ Hàng đợi (Queue), Ngăn xếp (Stack) cho đến Cây nhị phân (BST) của hệ thống quản lý nhà hàng đều thao tác trên một đối tượng chung: Món ăn. 

##                 ##
typedef struct {
    char maMon[20];
    char tenMon[50];
    int giaTien;
} MonAn;
##                 ##

File restaurant.h
 

                                                            //  WORKFLOW  \\
GIAI ĐOẠN 1: KHỞI ĐỘNG HỆ THỐNG

Mục tiêu: Chuẩn bị toàn bộ dữ liệu trước khi người dùng thao tác.

## Bước 1: Khởi động chương trình

Người dùng mở chương trình.

Hệ thống tạo các vùng nhớ cần thiết để quản lý:

   - Danh sách món ăn.
   - Hàng đợi đặt món.
   - Ngăn xếp hoàn tác.
   - Cây tìm kiếm.

Lúc này tất cả đều đang rỗng.

## Bước 2: Đọc dữ liệu từ file

Hệ thống mở file restaurant.txt.

Nếu file đã có dữ liệu thì:

   - Đọc từng món ăn.
   - Đưa từng món vào danh sách quản lý.

Nếu file chưa có dữ liệu thì bắt đầu với danh sách rỗng.

## Bước 3: Tạo cây tìm kiếm

Sau khi đã có danh sách món ăn, hệ thống xây dựng cây BST từ toàn bộ danh sách.

Việc này giúp sau này tìm kiếm theo mã nhanh hơn.
 
## Bước 4: Hiển thị Menu

Sau khi dữ liệu đã sẵn sàng, hệ thống hiển thị menu để người dùng chọn chức năng.

GIAI ĐOẠN 2: QUẢN LÝ THỰC ĐƠN

Đây là phần người dùng sử dụng nhiều nhất.

Chức năng Thêm món

Người dùng nhập:

   - Mã món.
   - Tên món.
   - Giá.

Hệ thống sẽ:

    Kiểm tra mã món đã tồn tại hay chưa.
    Nếu trùng thì báo lỗi.
    Nếu không trùng thì thêm vào danh sách.
    Lưu thao tác để sau này có thể Undo.
    Cập nhật lại cây BST.
    Ghi lịch sử thao tác.

- Chức năng Hiển thị

Người dùng chọn "Hiển thị danh sách".

Hệ thống in toàn bộ thực đơn ra màn hình dưới dạng bảng.

- Chức năng Xóa

Người dùng nhập mã món muốn xóa.

Hệ thống:

    Kiểm tra món có tồn tại hay không.
    Lưu lại thông tin món ăn trước khi xóa.
    Xóa món khỏi danh sách.
    Cập nhật lại cây BST.
    Ghi lịch sử thao tác.

- Chức năng Cập nhật

Người dùng nhập mã món.

Sau đó nhập giá mới.

Hệ thống:

    Tìm món cần sửa.
    Lưu lại dữ liệu cũ.
    Cập nhật dữ liệu mới.
    Cập nhật lại cây BST.
    Ghi lịch sử.

- Chức năng Tìm kiếm

Người dùng có thể:

    Tìm theo mã.
    Tìm theo tên.
    Tìm theo khoảng giá.

Nếu tìm theo mã sẽ sử dụng cây BST để tăng tốc.

Các trường hợp còn lại sẽ tìm trên danh sách liên kết.

- Chức năng Sắp xếp

Người dùng có thể:

    Sắp xếp theo tên.
    Sắp xếp theo giá.

Sau khi sắp xếp xong, hệ thống hiển thị lại danh sách.

GIAI ĐOẠN 3: QUẢN LÝ ĐẶT MÓN

Đây là phần mô phỏng hoạt động của nhà hàng.

Khách gọi món

Thu ngân nhập mã món.

Hệ thống:

    Kiểm tra món có tồn tại.
    Đưa món đó vào cuối hàng đợi.

Khách nào gọi trước sẽ đứng trước.

Bếp phục vụ

Khi bếp hoàn thành một món.

Hệ thống:

    Lấy món ở đầu hàng đợi.
    Cộng giá tiền món đó vào doanh thu.
    Ghi lịch sử đã phục vụ.

Luôn phục vụ theo nguyên tắc vào trước - ra trước (FIFO).

GIAI ĐOẠN 4: HOÀN TÁC (UNDO)

Nếu người dùng thao tác nhầm.

Ví dụ:

    Thêm nhầm.
    Xóa nhầm.
    Sửa nhầm.

Thì hệ thống sẽ:

    Lấy thông tin đã lưu trong Stack.
    Khôi phục lại trạng thái trước đó.
    Cập nhật lại cây BST.
    Ghi thêm lịch sử hoàn tác.

Nguyên tắc là thao tác thực hiện sau sẽ được hoàn tác trước (LIFO).

GIAI ĐOẠN 5: THOÁT CHƯƠNG TRÌNH

Khi người dùng chọn Thoát.

Hệ thống sẽ:

Bước 1

Lưu toàn bộ danh sách món ăn xuống file restaurant.txt.

Bước 2

Giải phóng toàn bộ bộ nhớ đã cấp phát cho:

Danh sách liên kết.
    Queue.
    Stack.
    BST.
Bước 3

Đóng chương trình.