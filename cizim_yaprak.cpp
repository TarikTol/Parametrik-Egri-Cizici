#include <iostream>
#include <cmath>
#include "canvas.cpp" 
const double PI = acos(-1.0); // PI sayısı
using namespace std;

// 1. KUTUPSAL DENKLEM: r = f(theta)


double Kutupsal_R_Fonksiyonu(double theta) {
    double a = 15.0; 
    double n = 3.0; 
    
    // Şekli orijin etrafında ne kadar döndürmek istiyorsan o açıyı (radyan) buraya yaz:
    double dondurmeAcisi = PI / 3.0; // Örn: PI/4 (45 derece) //Döndürmek istemiyorsanız 0 yazabilirsinixz

    // Formüldeki her theta yerine (theta - dondurmeAcisi) yazıyoruz:
    return a * sin(n * (theta - dondurmeAcisi)); //İstediğiniz trigonometri fonksiyonunu kullanabilirsiniz,
    // örneğin cos veya tan gibi. Sinüs ve kosinüs genellikle yaprak benzeri şekiller için güzel sonuç verir.
}
// 2. KARTEZYEN X DÖNÜŞÜMÜ: x = r * cos(theta)
double Parametrik_X_Fonksiyonu(double theta) {
    double r = Kutupsal_R_Fonksiyonu(theta); // O anki açının r uzunluğunu al
    return r * cos(theta);                   // X eksenine izdüşümünü bul
}

// 3. KARTEZYEN Y DÖNÜŞÜMÜ: y = r * sin(theta)
double Parametrik_Y_Fonksiyonu(double theta) {
    double r = Kutupsal_R_Fonksiyonu(theta); // O anki açının r uzunluğunu al
    return r * sin(theta);                   // Y eksenine izdüşümünü bul
}

//MAIN FONKSİYONU

int main() {
    const int iterasyon_sayisi = 20000; 
    double* px = new double[iterasyon_sayisi];
    double* py = new double[iterasyon_sayisi];

    
    // Tam bir tur atarak tüm yaprakları tamamlamak için 0'dan 2*PI'ye gidiyoruz
    double d_theta = (2.0 * PI) / iterasyon_sayisi; 

    // Her bir adımı (açıyı) tarayarak noktaları dizilere kaydediyoruz
    for(int i = 0; i < iterasyon_sayisi; i++) {
        double theta = i * d_theta;

        px[i] = Parametrik_X_Fonksiyonu(theta);
        py[i] = Parametrik_Y_Fonksiyonu(theta);
    }

    //buradaki 10.0'lar x ve y'nin  ölçekleridir, örneğin1.0 ve 10.0 olursa
    //x'e kıyasla y'ler daha büyük olur
    //500 ve 500 ise 1000-1000'lik bir tuvalin tam ortasına çizim yapar, eğer 0 ve 0 olsaydı yapraklar sol alt köşeye çizilirdi
    canvas cizim("Yapraklar", 20.0, 20.0, 500, 500); 
    
    cizim.drawFrame(); // Arka plana eksenleri ve ızgarayı çiz
    
    // px ve py dizilerindeki noktaları birleştirme işlemi
    cizim.drawPolyline(px, py, iterasyon_sayisi, "red");

    // Bellek Temizliği 
    delete[] px;
    delete[] py;
    px = nullptr;
    py = nullptr;
    
    return 0;
}