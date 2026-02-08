# C'de ATM Similasyon Sistemi 

Bu proje, C programlama dili kullanılarak geliştirilmiş, temel bankacılık işlemlerini simüle eden bir konsol uygulamasıdır. Dosya tabanlı veri saklama yapısı sayesinde kullanıcı bilgileri kalıcı olarak tutulur.

## 🚀 Özellikler
- **Hesap Oluşturma:** Benzersiz (unique) ID üretimi ve kullanıcı kaydı.
- **Güvenli Giriş:** ID ve PIN eşleşmesi kontrolü.
- **Bakiye Yönetimi:** Para yatırma, çekme ve bakiye sorgulama.
- **Veri Kalıcılığı:** Tüm veriler `.dat` uzantılı binary dosyada saklanır.

## 🛠️ Teknik Detaylar
- **Dil:** C
- **Veri Yapıları:** Struct, Binary File I/O
- **Platform:** Windows (conio.h ve Windows.h bağımlılıkları içerir)

## 📌 Nasıl Çalıştırılır?
1. Herhangi bir C derleyicisi (GCC, Visual Studio, Dev-C++) ile `main.c` dosyasını derleyin.
2. Oluşan `.exe` dosyasını çalıştırın.
3. Önce "Yeni Hesap Oluştur" seçeneği ile kayıt olun, ardından giriş yapın.

## 📈 Geliştirme Planı (Roadmap)
- [ ] `fseek()` kullanarak daha performanslı dosya güncelleme sistemi.
- [ ] Şifrelerin SHA-256 ile hashlenerek saklanması.
- [ ] Çoklu dil desteği.
- [ ] Harf/Rakam giriş hatalarına karşı `input validation` mekanizması.

