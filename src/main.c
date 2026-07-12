#include "../include/restaurant.h"

/*=========================================================
    CAU HINH DUONG DAN FILE DU LIEU (MACROS)
=========================================================*/
// Lùi ra khỏi phòng src/ (dùng ../) để truy cập vào folder data/
#define FILE_MENU "../data/restaurant.txt"
#define FILE_HIST "../data/history.txt"

/*=========================================================
    CAC HAM HO TRO NHAP LIEU & GIAO DIEN (UI WRAPPERS)
=========================================================*/

/*
 * Xoa bo nho dem, chong troi lenh khi nhap chuoi sau khi nhap so
 */
static void xoaBoNhoDem(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Vòng lặp rỗng để hút sạch ký tự thừa trong bộ nhớ đệm
    }
}

/*
 * Tim nhanh mon an theo ma de lay thong tin cu (Phục vụ Undo)
 */
static int layThongTinMonCu(Node* head, char* maMon, MonAn* monCu)
{
    Node* p = head;

    while (p != NULL)
    {
        if (strcmp(p->data.maMon, maMon) == 0)
        {
            *monCu = p->data;
            return 1; // Tìm thấy
        }
        p = p->next;
    }

    return 0; // Không tìm thấy
}

/*
 * Giao dien: Them mon an moi (Case 2 - Module 1 Phat)
 */
static void uiThemMon(Node** menuHead, StackNode** undoTop, HistoryNode** histHead, HistoryNode** histTail, TreeNode** bstRoot)
{
    MonAn monMoi;
    printf("\n--- THEM MON AN MOI ---\n");
    printf("Nhap ma mon (vd: M01): ");
    scanf("%19s", monMoi.maMon);
    xoaBoNhoDem();

    if (kiemTraTrungMa(*menuHead, monMoi.maMon))
    {
        printf("[LOI] Ma mon [%s] da ton tai!\n", monMoi.maMon);
        return;
    }

    printf("Nhap ten mon an: ");
    scanf("%49[^\n]", monMoi.tenMon);
    xoaBoNhoDem();

    printf("Nhap gia tien (VND): ");
    scanf("%d", &monMoi.giaTien);
    xoaBoNhoDem();

    // 1. Thêm vào Danh sách liên kết (Phát)
    themMonAn(menuHead, monMoi);
    // 2. Thêm vào cây BST tốc độ cao (Hoàng)
    *bstRoot = themVaoCayBST(*bstRoot, monMoi);
    // 3. Ghi vào Stack Undo & Nhật ký hệ thống (Lê)
    pushUndo(undoTop, THEM, monMoi);

    char logMsg[150];
    sprintf(logMsg, "Them mon moi: [%s - %s]", monMoi.maMon, monMoi.tenMon);
    addHistory(histHead, histTail, logMsg);

    printf("=> Them mon an thanh cong!\n");
}

/*
 * Giao dien: Xoa mon an theo Ma (Case 3) - DA TU DONG HIEN MENU TRUOC
 */
static void uiXoaMon(Node** menuHead, StackNode** undoTop, HistoryNode** histHead, HistoryNode** histTail)
{
    char maXoa[20];
    MonAn monCu;

    printf("\n--- XOA MON AN ---\n");
    
    // [UX IMPROVEMENT]: In danh sách ra trước để người dùng nhìn mã món
    printf("Danh sach thuc don hien tai:\n");
    hienThiDanhSach(*menuHead); 

    printf("=> Nhap MA MON can xoa tu danh sach tren: ");
    scanf("%19s", maXoa);
    xoaBoNhoDem();

    if (layThongTinMonCu(*menuHead, maXoa, &monCu))
    {
        xoaMonAnTheoMa(menuHead, maXoa);
        pushUndo(undoTop, XOA, monCu);

        char logMsg[150];
        sprintf(logMsg, "Xoa mon an: [%s - %s]", monCu.maMon, monCu.tenMon);
        addHistory(histHead, histTail, logMsg);
        printf("=> Da xoa mon [%s] thanh cong!\n", maXoa);
    }
    else
    {
        printf("[LOI] Khong tim thay mon co ma [%s] trong thuc don!\n", maXoa);
    }
}

/*
 * Giao dien: Cap nhat gia mon an (Case 4) - DA TU DONG HIEN MENU TRUOC
 */
static void uiSuaGia(Node* menuHead, StackNode** undoTop, HistoryNode** histHead, HistoryNode** histTail)
{
    char maSua[20];
    int giaMoi;
    MonAn monCu;

    printf("\n--- CAP NHAT GIA MON AN ---\n");
    
    // [UX IMPROVEMENT]: In danh sách ra trước để người dùng chọn mã món
    printf("Danh sach thuc don hien tai:\n");
    hienThiDanhSach(menuHead);

    printf("=> Nhap MA MON can sua gia tu danh sach tren: ");
    scanf("%19s", maSua);
    xoaBoNhoDem();

    if (layThongTinMonCu(menuHead, maSua, &monCu))
    {
        printf("Mon [%s - %s] dang co gia: %d VND.\n", monCu.maMon, monCu.tenMon, monCu.giaTien);
        printf("=> Nhap gia moi (VND): ");
        scanf("%d", &giaMoi);
        xoaBoNhoDem();

        capNhatGiaTien(menuHead, maSua, giaMoi);
        pushUndo(undoTop, SUA, monCu);

        char logMsg[150];
        sprintf(logMsg, "Sua gia mon [%s] tu %d thanh %d VND", monCu.maMon, monCu.giaTien, giaMoi);
        addHistory(histHead, histTail, logMsg);
        printf("=> Da cap nhat gia moi thanh cong!\n");
    }
    else
    {
        printf("[LOI] Khong tim thay mon co ma [%s] trong thuc don!\n", maSua);
    }
}

/*
 * Giao dien: Dat mon vao Bep (Case 6 - Module 2 Le)
 */
static void uiDatMon(Node* menuHead, OrderNode** queueFront, OrderNode** queueRear, HistoryNode** histHead, HistoryNode** histTail)
{
    char maOrder[20];
    int soLuong;
    MonAn monOrder;

    printf("\n--- DAT MON (SEND TO KITCHEN QUEUE) ---\n");
    printf("Danh sach thuc don hien tai:\n");
    hienThiDanhSach(menuHead);

    printf("=> Nhap MA MON khach goi: ");
    scanf("%19s", maOrder);
    xoaBoNhoDem();

    if (layThongTinMonCu(menuHead, maOrder, &monOrder))
    {
        printf("Nhap so luong mon [%s]: ", monOrder.tenMon);
        scanf("%d", &soLuong);
        xoaBoNhoDem();

        if (soLuong <= 0)
        {
            printf("[LOI] So luong phai lon hon 0!\n");
            return;
        }

        enqueueOrder(queueFront, queueRear, monOrder, soLuong);

        char logMsg[150];
        sprintf(logMsg, "Khach order: [%s] x %d", monOrder.tenMon, soLuong);
        addHistory(histHead, histTail, logMsg);
    }
    else
    {
        printf("[LOI] Mon co ma [%s] khong co trong thuc don!\n", maOrder);
    }
}

/*
 * Giao dien: Tim kiem mon an (Case 10 - Module 3 Hoang)
 */
static void uiTimKiem(Node* menuHead, TreeNode* bstRoot)
{
    int chonTim;
    printf("\n--- TIM KIEM MON AN ---\n");
    printf("1. Tim theo Ten mon an (Linked List - Phat)\n");
    printf("2. Tim theo Khoang gia (Linked List - Phat)\n");
    printf("3. Tim theo Ma mon (Cay BST toc do cao - Hoang)\n");
    printf("=> Chon (1-3): ");
    scanf("%d", &chonTim);
    xoaBoNhoDem();

    if (chonTim == 1)
    {
        char tenTim[50];
        printf("Nhap ten mon can tim: ");
        scanf("%49[^\n]", tenTim);
        xoaBoNhoDem();
        timKiemTheoTen(menuHead, tenTim);
    }
    else if (chonTim == 2)
    {
        int min, max;
        printf("Nhap gia thap nhat (Min): ");
        scanf("%d", &min);
        printf("Nhap gia cao nhat (Max): ");
        scanf("%d", &max);
        xoaBoNhoDem();
        timKiemTheoKhoangGia(menuHead, min, max);
    }
    else if (chonTim == 3)
    {
        char maTim[20];
        printf("Nhap ma mon can tim tren cay BST: ");
        scanf("%19s", maTim);
        xoaBoNhoDem();

        TreeNode* ketQua = timKiemTheoMaBST(bstRoot, maTim);
        if (ketQua != NULL)
        {
            printf("\n[TIM THAY TREN BST] => Ma: %s | Ten: %s | Gia: %d VND\n",
                   ketQua->data.maMon, ketQua->data.tenMon, ketQua->data.giaTien);
        }
        else
        {
            printf("\n[KHONG TIM THAY] Khong co mon [%s] tren cay BST!\n", maTim);
        }
    }
    else
    {
        printf("Lua chon khong hop le!\n");
    }
}

/*
 * Giao dien: Sap xep thuc don (Case 11 - Module 3 Hoang)
 */
static void uiSapXep(Node** menuHead)
{
    int chonSapXep, tangDan;
    printf("\n--- SAP XEP THUC DON (HOANG) ---\n");
    printf("1. Sap xep theo MA MON\n");
    printf("2. Sap xep theo TEN MON\n");
    printf("3. Sap xep theo GIA TIEN\n");
    printf("=> Chon tieu chi (1-3): ");
    scanf("%d", &chonSapXep);

    printf("Chon thu tu (1: Tang dan | 0: Giam dan): ");
    scanf("%d", &tangDan);
    xoaBoNhoDem();

    if (chonSapXep == 1)
    {
        sapXepTheoMa(menuHead, tangDan);
        printf("=> Da sap xep theo MA MON %s!\n", tangDan ? "Tang Dan" : "Giam Dan");
    }
    else if (chonSapXep == 2)
    {
        sapXepTheoTen(menuHead, tangDan);
        printf("=> Da sap xep theo TEN MON %s!\n", tangDan ? "Tang Dan" : "Giam Dan");
    }
    else if (chonSapXep == 3)
    {
        sapXepTangTheoGia(menuHead, tangDan);
        printf("=> Da sap xep theo GIA TIEN %s!\n", tangDan ? "Tang Dan" : "Giam Dan");
    }
    else
    {
        printf("Lua chon khong hop le!\n");
        return;
    }

    // In ngay danh sách sau khi sắp xếp cho người dùng kiểm chứng
    hienThiDanhSach(*menuHead);
}

/*
 * In khung Menu chinh cua chung trinh
 */
static void inMenuChinh(void)
{
    printf("\n");
    printf("******************************************************************\n");
    printf("* CHUNG TRINH QUAN LY NHA HANG - DO AN NHOM 6               *\n");
    printf("* (Thanh vien: Phat - Le - Hoang)                     *\n");
    printf("******************************************************************\n");
    printf("* [MODULE 1: QUAN LY THUC DON - PHAT]                            *\n");
    printf("* 1. Hien thi danh sach thuc don                               *\n");
    printf("* 2. Them mon an moi (Co ghi Undo & Log)                       *\n");
    printf("* 3. Xoa mon an theo Ma (Co ghi Undo & Log)                    *\n");
    printf("* 4. Cap nhat gia mon an (Co ghi Undo & Log)                   *\n");
    printf("* 5. Sao luu / Khoi phuc thuc don thu cong voi file (data/...) *\n");
    printf("* *\n");
    printf("* [MODULE 2: QUAN LY DON HANG & HOAN TAC - LE]                   *\n");
    printf("* 6. Dat mon vao hang doi Bep (Queue Order)                    *\n");
    printf("* 7. Phuc vu mon (Bep lam xong - Dequeue)                      *\n");
    printf("* 8. HOAN TAC thao tac gan nhat (Ctrl + Z - Stack)             *\n");
    printf("* 9. Xem & Ghi nhat ky hoat dong ra file (history.txt)         *\n");
    printf("* *\n");
    printf("* [MODULE 3: TIM KIEM & SAP XEP - HOANG]                         *\n");
    printf("* 10. Tim kiem mon an (Theo Ten / Khoang Gia / Cay BST)        *\n");
    printf("* 11. Sap xep thuc don (Theo Ma / Ten / Gia)                   *\n");
    printf("******************************************************************\n");
    printf("* 0. THOAT CHUNG TRINH & GIAI PHONG BO NHO RAM                 *\n");
    printf("******************************************************************\n");
    printf("=> Nhap lua chon cua ban (0 - 11): ");
}

/*=========================================================
    HAM CHINH - MAIN FUNCTION (SIÊU NGẮN, SIÊU SẠCH)
=========================================================*/
int main(void)
{
    // 1. Khởi tạo các con trỏ quản lý của 3 thành viên
    Node* menuHead = NULL;          // Phát: Danh sách liên kết thực đơn
    OrderNode* queueFront = NULL;   // Lê: Đầu hàng đợi đơn hàng
    OrderNode* queueRear = NULL;    // Lê: Đuôi hàng đợi đơn hàng
    StackNode* undoTop = NULL;      // Lê: Đỉnh ngăn xếp hoàn tác
    HistoryNode* histHead = NULL;   // Lê: Đầu danh sách nhật ký
    HistoryNode* histTail = NULL;   // Lê: Đuôi danh sách nhật ký
    TreeNode* bstRoot = NULL;       // Hoàng: Gốc cây nhị phân tìm kiếm

    int luaChon;

    // 2. Tự động nạp dữ liệu từ file lúc khởi động & Đồng bộ sang cây BST
    docDuLieuTuFile(&menuHead, FILE_MENU);
    
    Node* p = menuHead;
    while (p != NULL)
    {
        bstRoot = themVaoCayBST(bstRoot, p->data);
        p = p->next;
    }

    addHistory(&histHead, &histTail, "He thong khoi dong va nap du lieu tu data/restaurant.txt");

    // 3. Vòng lặp Menu chính
    while (1)
    {
        inMenuChinh();

        // Kiểm tra chống trôi lệnh khi nhập chữ vào ô số
        if (scanf("%d", &luaChon) != 1)
        {
            printf("\n[LOI] Vui long nhap mot so nguyen hop le!\n");
            xoaBoNhoDem();
            continue;
        }
        xoaBoNhoDem();

        switch (luaChon)
        {
            case 1:
            {
                hienThiDanhSach(menuHead);
                break;
            }
            case 2:
            {
                uiThemMon(&menuHead, &undoTop, &histHead, &histTail, &bstRoot);
                break;
            }
            case 3:
            {
                uiXoaMon(&menuHead, &undoTop, &histHead, &histTail);
                break;
            }
            case 4:
            {
                uiSuaGia(menuHead, &undoTop, &histHead, &histTail);
                break;
            }
            case 5: // Sao luu / Khoi phuc thu cong (Module 1)
            {
                int chonFile;
                printf("\n--- QUAN LY FILE THUC DON ---\n");
                printf("1. Ghi thuc don hien tai ra file (%s)\n", FILE_MENU);
                printf("2. Doc thuc don tu file (%s) vao RAM\n", FILE_MENU);
                printf("=> Chon (1-2): ");
                scanf("%d", &chonFile);
                xoaBoNhoDem();

                if (chonFile == 1)
                {
                    ghiDuLieuRaFile(menuHead, FILE_MENU);
                    addHistory(&histHead, &histTail, "Sao luu thuc don ra file restaurant.txt");
                    printf("=> Da ghi sao luu thuc don ra file thanh cong!\n");
                }
                else if (chonFile == 2)
                {
                    // [UX IMPROVEMENT]: 1. Dọn sạch Menu & BST cũ trong RAM trước để không bị lỗi trùng mã
                    giaiPhongDanhSach(menuHead);
                    menuHead = NULL;

                    giaiPhongCay(bstRoot);
                    bstRoot = NULL;

                    // 2. Nạp lại từ đầu vào RAM sạch
                    docDuLieuTuFile(&menuHead, FILE_MENU);

                    // 3. Đồng bộ dữ liệu vừa đọc sang cây BST của Hoàng
                    Node* ptr = menuHead;
                    while (ptr != NULL)
                    {
                        bstRoot = themVaoCayBST(bstRoot, ptr->data);
                        ptr = ptr->next;
                    }

                    addHistory(&histHead, &histTail, "Nap lai du lieu thuc don tu file restaurant.txt");
                    printf("=> Da khoi phuc thuc don tu file vao RAM thanh cong!\n");
                }
                else
                {
                    printf("Lua chon khong hop le!\n");
                }
                break;
            }
            case 6:
            {
                uiDatMon(menuHead, &queueFront, &queueRear, &histHead, &histTail);
                break;
            }
            case 7:
            {
                printf("\n--- PHUC VU MON AN ---");
                dequeueOrder(&queueFront, &queueRear);
                addHistory(&histHead, &histTail, "Bep hoan thanh va phuc vu 1 don hang");
                break;
            }
            case 8:
            {
                printf("\n--- HOAN TAC THAO TAC GAN NHAT ---");
                popUndo(&undoTop, &menuHead);
                addHistory(&histHead, &histTail, "Thuc hien hoan tac (Undo)");
                break;
            }
            case 9: // Xem & Ghi nhat ky hoat dong (Module 2 - Le)
            {
                printf("\n--- NHAT KY HOAT DONG CUA HE THONG (LOG HISTORY) ---\n");
                
                char xacNhan;
                printf("Ban co muon xuat nhat ky hoat dong ra file %s? (y/n): ", FILE_HIST);
                scanf("%c", &xacNhan);
                xoaBoNhoDem();

                if (xacNhan == 'y' || xacNhan == 'Y')
                {
                    ghiFileHistory(histHead, FILE_HIST);
                    printf("=> Da xuat nhat ky ra file %s thanh cong!\n", FILE_HIST);
                }
                break;
            }
            case 10:
            {
                uiTimKiem(menuHead, bstRoot);
                break;
            }
            case 11:
            {
                uiSapXep(&menuHead);
                break;
            }
            case 0: // Thoat & Giai phong bo nho RAM
            {
                printf("\n=======================================================\n");
                printf("DANG DON DEP BO NHO RAM VA THOAT CHUNG TRINH...\n");
                
                // Tự động lưu thực đơn ra file restaurant.txt trước khi tắt máy
                ghiDuLieuRaFile(menuHead, FILE_MENU);

                // Gọi hàm giải phóng RAM của từng module
                giaiPhongDanhSach(menuHead);
                giaiPhongModule2(&queueFront, &undoTop, &histHead);
                giaiPhongCay(bstRoot);

                printf("=> Da giai phong 100%% RAM. Tam biet Nhom 6!\n");
                printf("=======================================================\n");
                return 0; // Tắt chương trình thành công
            }
            default:
            {
                printf("\n[LOI] Lua chon khong hop le! Vui long nhap tu 0 den 11.\n");
                break;
            }
        }
    }

    return 0;
}