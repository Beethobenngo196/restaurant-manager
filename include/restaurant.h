#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =========================================================
   PHẦN 1: ĐỊNH NGHĨA CẤU TRÚC DỮ LIỆU CỐT LÕI
========================================================= */

// 1.1. Cấu trúc một món ăn (Thực thể chính)
typedef struct {
    char maMon[20];
    char tenMon[50];
    int giaTien;
} MonAn;

// 1.2. Cấu trúc Node (Dùng chung cho Danh sách liên kết, Queue)
typedef struct Node {
    MonAn data;
    struct Node* next;
} Node;

// 1.2. Cấu trúc OrderNode (Hàng đợi có số lượng)
typedef struct OrderNode {
    MonAn data;
    int soLuong;
    struct OrderNode* next;
} OrderNode;

// 1.3. Cấu trúc riêng cho Stack (Phục vụ Undo Thêm/Xóa/Sửa)
typedef enum {
    THEM,
    XOA,
    SUA
} LoaiThaoTac;

typedef struct StackNode {
    LoaiThaoTac loai;    // Đánh dấu đây là thao tác gì
    MonAn thongTinCu;    // Lưu lại trạng thái của món ăn để phục hồi
    struct StackNode* next;
} StackNode;

// 1.3. Cấu trúc HistoryNode (Danh sách kép - Lưu vết thao tác)    
typedef struct HistoryNode {
    char timestamp[10];
    char description[150];
    struct HistoryNode* prev;
    struct HistoryNode* next;
} HistoryNode;

// 1.4. Cấu trúc TreeNode (Dùng riêng cho Cây nhị phân tìm kiếm - BST)
typedef struct TreeNode {
    MonAn data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


/* =========================================================
   PHẦN 2: KHAI BÁO HÀM - PHÂN CÔNG NHIỆM VỤ
========================================================= */

// ---------------------------------------------------------
// NHIỆM VỤ 1 : Quản lý Danh sách & File I/O (CRUD) - GIỮ NGUYÊN 100%
// ---------------------------------------------------------

void khoiTaoDanhSach(Node** head);


int kiemTraTrungMa(Node* head, char* maMon);
void themMonAn(Node** head, MonAn monMoi);
void hienThiDanhSach(Node* head);
void xoaMonAnTheoMa(Node** head, char* maMon);
void xoaMonAnTheoTen(Node** head, char* tenMon);
void capNhatGiaTien(Node* head, char* maMon, int giaMoi);
void docDuLieuTuFile(Node** head, const char* tenFile);
void ghiDuLieuRaFile(Node* head, const char* tenFile);

// Giải phóng bộ nhớ cho Danh sách liên kết
void giaiPhongDanhSach(Node* head);

// ---------------------------------------------------------
// NHIỆM VỤ 2 : Stack (Undo), Queue (Order) & Lịch sử
// ---> [CHỈ CẬP NHẬT CHỮ KÝ HÀM BLOCK NÀY CHO KHỚP VỚI LE.C]
// ---------------------------------------------------------
// Xử lý Stack (Hoàn tác)
void pushUndo(StackNode** top, LoaiThaoTac loai, MonAn mon);
void popUndo(StackNode** top, Node** headMainList);

// Xử lý Queue (Đặt món - FIFO)
void enqueueOrder(OrderNode** front, OrderNode** rear, MonAn mon, int soLuong);
void dequeueOrder(OrderNode** front, OrderNode** rear);

// Lưu vết thao tác (Danh sách kép) & Thống kê
void addHistory(HistoryNode** head, HistoryNode** tail, char* description);
void ghiFileHistory(HistoryNode* head, const char* tenFile);
long long tinhTongDoanhThu(OrderNode* queueDaPhucVu);
double tinhGiaTrungBinhMenu(Node* head);
void thongKeDuLieu(OrderNode* queueHead, Node* menuHead);

// Giải phóng bộ nhớ cho Queue, Stack, History
void giaiPhongQueue(OrderNode** front);
void giaiPhongStack(StackNode** top);
void giaiPhongHistory(HistoryNode** head);
void giaiPhongModule2(OrderNode** queueHead, StackNode** undoTop, HistoryNode** historyHead);

// ---------------------------------------------------------
// NHIỆM VỤ 3 : Cây BST (Tìm kiếm), Sắp xếp danh sách - GIỮ NGUYÊN 100%
// ---------------------------------------------------------
// Xử lý Cây nhị phân tìm kiếm
TreeNode* themVaoCayBST(TreeNode* root, MonAn mon);
void duyetCayInorder(TreeNode* root);  // In ra danh sách tăng dần theo mã
void duyetCayPreorder(TreeNode* root);
void duyetCayPostorder(TreeNode* root);
TreeNode* timKiemTheoMaBST(TreeNode* root, char* maMon);
void timKiemTheoTen(Node* head, char* tenMon);
void timKiemTheoKhoangGia(Node* head, int giaMin, int giaMax);
// Thuật toán sắp xếp trên Danh sách liên kết
void sapXepTheoTen(Node** head, int tangDan);
void sapXepTheoMa(Node** head, int tangDan);
void sapXepTangTheoGia(Node** head, int tangDan);
// Giải phóng bộ nhớ cho Cây BST
void giaiPhongCay(TreeNode* root);

#endif