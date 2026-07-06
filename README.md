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

