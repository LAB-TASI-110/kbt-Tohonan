#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk exit(), rand(), srand()
#include <time.h>   // Untuk time()

#define MAX_NAMA 50
#define MAX_WA 15
#define MAX_TGL 20
#define MAX_ALAMAT 20 // Untuk lokasi saat ini
#define MAX_TUJUAN 20
#define MAX_KONFIRMASI 5
#define MAX_NO_MOBIL 7 // Ukuran string untuk nomor mobil (e.g., "KBT-01")
#define MAX_KELAS 10 // Untuk menyimpan string kelas (Economy/Executive)

int main() {
    // Inisialisasi generator angka acak
    srand(time(NULL)); 

    char nama[MAX_NAMA];
    char no_wa[MAX_WA];
    char tgl_berangkat[MAX_TGL];
    char lokasi_saat_ini_str[MAX_ALAMAT];
    char tujuan_str[MAX_TUJUAN];
    int pilihan_lokasi, pilihan_tujuan, pilihan_kelas;
    long harga_tiket_economy = 0; // Harga dasar untuk kelas Economy
    long harga_tiket_final = 0;   // Harga akhir setelah penyesuaian kelas
    char konfirmasi_bayar[MAX_KONFIRMASI];
    char no_va[20]; // Nomor Virtual Account
    char kelas_tiket_str[MAX_KELAS]; // Menyimpan string "ECONOMY" atau "EXECUTIVE"

    // Daftar nomor mobil yang tersedia (7 mobil, sesuai minimal 3, maksimal 10)
    const char *daftar_mobil[] = {"KBT-01", "KBT-02", "KBT-03", "KBT-04", "KBT-05", "KBT-06", "KBT-07"};
    int jumlah_mobil_tersedia = sizeof(daftar_mobil) / sizeof(daftar_mobil[0]);
    char no_mobil_terpilih[MAX_NO_MOBIL]; // Variabel untuk menyimpan nomor mobil yang dipilih sistem

    printf("=== Sistem Ticketing Koperasi Bintang Tapanuli (KBT) ===\n");

    // Input data pelanggan
    printf("Masukkan Nama: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Menghapus newline

    printf("Masukkan Nomor WA: ");
    fgets(no_wa, sizeof(no_wa), stdin);
    no_wa[strcspn(no_wa, "\n")] = 0;

    printf("Masukkan Tanggal Berangkat (contoh: 3 Maret 2026): ");
    fgets(tgl_berangkat, sizeof(tgl_berangkat), stdin);
    tgl_berangkat[strcspn(tgl_berangkat, "\n")] = 0;

    // Sistem memilih nomor mobil secara acak
    int indeks_mobil_acak = rand() % jumlah_mobil_tersedia;
    strcpy(no_mobil_terpilih, daftar_mobil[indeks_mobil_acak]);
    printf("Sistem telah memilihkan Nomor Mobil untuk Anda: %s\n", no_mobil_terpilih);

    // Pilihan lokasi keberangkatan saat ini
    printf("\nPilih Lokasi Keberangkatan Anda Saat Ini:\n");
    printf("1. Medan\n");
    printf("2. Jawa\n");
    printf("3. Siborongborong\n");
    printf("Masukkan pilihan Anda (1/2/3): ");
    scanf("%d", &pilihan_lokasi);
    while (getchar() != '\n'); // Membersihkan buffer input setelah scanf

    // Pilihan tujuan berdasarkan lokasi keberangkatan dan penetapan harga Economy
    printf("\nPilih Tujuan Anda:\n");
    switch (pilihan_lokasi) {
        case 1: // Lokasi saat ini: Medan
            strcpy(lokasi_saat_ini_str, "Medan");
            printf("1. Siborongborong\n");
            printf("2. Jawa\n");
            printf("Masukkan pilihan Anda (1/2): ");
            scanf("%d", &pilihan_tujuan);
            while (getchar() != '\n');
            if (pilihan_tujuan == 1) {
                strcpy(tujuan_str, "Siborongborong");
                harga_tiket_economy = 90000;
            } else if (pilihan_tujuan == 2) {
                strcpy(tujuan_str, "Jawa");
                harga_tiket_economy = 200000;
            } else {
                printf("Pilihan tujuan tidak valid. Program dihentikan.\n");
                exit(1);
            }
            break;
        case 2: // Lokasi saat ini: Jawa
            strcpy(lokasi_saat_ini_str, "Jawa");
            printf("1. Medan\n");
            // Rute Jawa ke Siborongborong tidak ditawarkan karena harga tidak didefinisikan dalam prompt.
            printf("Masukkan pilihan Anda (1): ");
            scanf("%d", &pilihan_tujuan);
            while (getchar() != '\n');
            if (pilihan_tujuan == 1) {
                strcpy(tujuan_str, "Medan");
                harga_tiket_economy = 90000;
            } else {
                printf("Pilihan tujuan tidak valid. Program dihentikan.\n");
                exit(1);
            }
            break;
        case 3: // Lokasi saat ini: Siborongborong
            strcpy(lokasi_saat_ini_str, "Siborongborong");
            printf("1. Jawa\n");
            printf("2. Medan\n");
            printf("Masukkan pilihan Anda (1/2): ");
            scanf("%d", &pilihan_tujuan);
            while (getchar() != '\n');
            if (pilihan_tujuan == 1) {
                strcpy(tujuan_str, "Jawa");
                harga_tiket_economy = 300000;
            } else if (pilihan_tujuan == 2) {
                strcpy(tujuan_str, "Medan");
                harga_tiket_economy = 90000;
            } else {
                printf("Pilihan tujuan tidak valid. Program dihentikan.\n");
                exit(1);
            }
            break;
        default:
            printf("Pilihan lokasi keberangkatan tidak valid. Program dihentikan.\n");
            exit(1);
    }

    // Pilihan kelas KBT
    printf("\nPilih Kelas Tiket:\n");
    printf("1. KBT ECONOMY (Harga: Rp %ld)\n", harga_tiket_economy);
    printf("2. KBT EXECUTIVE (Harga: Rp %ld)\n", (long)(harga_tiket_economy * 1.5));
    printf("Masukkan pilihan Anda (1/2): ");
    scanf("%d", &pilihan_kelas);
    while (getchar() != '\n'); // Membersihkan buffer input setelah scanf

    if (pilihan_kelas == 1) {
        strcpy(kelas_tiket_str, "ECONOMY");
        harga_tiket_final = harga_tiket_economy;
    } else if (pilihan_kelas == 2) {
        strcpy(kelas_tiket_str, "EXECUTIVE");
        harga_tiket_final = (long)(harga_tiket_economy * 1.5); // Tambah 50%
    } else {
        printf("Pilihan kelas tiket tidak valid. Program dihentikan.\n");
        exit(1);
    }

    // Generate nomor VA sederhana (contoh: KBT-123456789)
    sprintf(no_va, "KBT-%010d", rand() % 1000000000); 

    printf("\n=== Rincian Pemesanan Tiket ===\n");
    printf("Nama Pelanggan    : %s\n", nama);
    printf("Nomor WA          : %s\n", no_wa);
    printf("Nomor Mobil       : %s\n", no_mobil_terpilih);
    printf("Tanggal Berangkat : %s\n", tgl_berangkat);
    printf("Lokasi Berangkat  : %s\n", lokasi_saat_ini_str);
    printf("Tujuan            : %s\n", tujuan_str);
    printf("Kelas Tiket       : KBT %s\n", kelas_tiket_str);
    printf("Harga Tiket       : Rp %ld\n", harga_tiket_final);
    printf("Nomor Virtual Account (VA) untuk pembayaran: %s\n", no_va);
    printf("Jumlah yang perlu dibayar: Rp %ld\n", harga_tiket_final);

    // Konfirmasi pembayaran
    printf("\nApakah Anda sudah membayar Nomor VA ini? (ya/tidak): ");
    fgets(konfirmasi_bayar, sizeof(konfirmasi_bayar), stdin);
    konfirmasi_bayar[strcspn(konfirmasi_bayar, "\n")] = 0;
    
    // Konversi ke lowercase untuk perbandingan yang lebih fleksibel
    for (int i = 0; konfirmasi_bayar[i]; i++) {
        if (konfirmasi_bayar[i] >= 'A' && konfirmasi_bayar[i] <= 'Z') {
            konfirmasi_bayar[i] = konfirmasi_bayar[i] + ('a' - 'A');
        }
    }

    if (strcmp(konfirmasi_bayar, "ya") == 0) {
        printf("\n=============================================\n");
        printf("Terima kasih, %s! Tiket Anda telah dikonfirmasi.\n", nama);
        printf("Anda akan mendapatkan konfirmasi lebih lanjut melalui WA: %s.\n", no_wa);
        printf("Selamat menikmati perjalanan Anda dengan KBT %s menggunakan mobil %s dari %s ke %s!\n", kelas_tiket_str, no_mobil_terpilih, lokasi_saat_ini_str, tujuan_str);
        printf("=============================================\n");
    } else {
        printf("\n=============================================\n");
        printf("Anda harus membayar agar bisa mendapatkan tiket.\n");
        printf("Silakan lakukan pembayaran ke Nomor VA: %s sejumlah Rp %ld.\n", no_va, harga_tiket_final);
        printf("=============================================\n");
    }

    return 0;
}