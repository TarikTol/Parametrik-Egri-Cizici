#include <iostream>
#include <cmath>
#include "canvas.cpp"
using namespace std;



//x'in t ye bağlı parametrik fonksiyonu
// x(t) = 16 * sin(t)^3
//eğer x(t) = 3*sint(t)+5 olsaydı kullanım şekli şu şekilde olurdu:
//... return  3.0*std::sin(t) + 5.0;
double Parametrik_X_Fonksiyonu(double t) {
    return 16.0 * pow(sin(t), 3);
}


//y'nin t ye bağlı parametrik fonksiyonu
// y(t) = 13cos(t) - 5cos(2t) - 2cos(3t) - cos(4t)
//eğer y(t) = t^2 + 4*t + 2 olsaydı kullanım şekli şu şekilde olurdu:
//... return std::pow(t, 2) + 4.0*t + 2.0;
double Parametrik_Y_Fonksiyonu(double t) {
    return 13.0 * cos(t) - 5.0 * cos(2.0 * t) - 2.0 * cos(3.0 * t) - cos(4.0 * t);
}





int main() {
    const int N = 2000;
    double* px = new double[N];
    double* py = new double[N];

    const double PI = acos(-1.0);
    double dt = (2.0 * PI) / N;

    
    for(int i = 0; i < N; i++) {
        double t = i * dt;

        px[i] = Parametrik_X_Fonksiyonu(t);
        
        py[i] = Parametrik_Y_Fonksiyonu(t);
    }

    canvas cizim("KALP", 10.0, 10.0, 500, 500); //buradaki 10.0'lar x ve y'nin  ölçekleridir, örneğin1.0 ve 10.0 olursa
    //x'e kıyasla y'ler daha büyük olur, örnekteki kalp daha çok bir "ok ucuna" benzer
    //500 ve 500 ise 1000-1000'lik bir tuvalin tam ortasına çizim yapar, eğer 0 ve 0 olsaydı kalp sol alt köşeye çizilirdi
    cizim.drawFrame();
    cizim.drawPolyline(px, py, N, "red");





    int ornekNoktaSayisi = 8; // 0'dan 2PI'ye kadar 8 nokta seçeceğiz
    double adimT = (2.0 * PI) / ornekNoktaSayisi; // PI/4 (45 derece) adımlarla

    for(int i = 0; i < ornekNoktaSayisi; i++) {
        double o_anki_t = i * adimT;
        
        // O spesifik t anındaki x ve y değerlerini fonksiyonlarından çekiyoruz
        double anlikX = Parametrik_X_Fonksiyonu(o_anki_t);
        double anlikY = Parametrik_Y_Fonksiyonu(o_anki_t);

        // 1. Orijinden (0,0) o noktaya Konum Vektörünü (Doğruyu) Çiziyoruz
        cizim.drawLine(0.0, 0.0, anlikX, anlikY, "blue");

        // 2. Tam o noktanın üzerine belirgin bir nokta koyuyoruz (Yarıçapı 3.0 olsun)
        cizim.drawPoint(anlikX, anlikY, "black", 3.0);

        // Noktanın hemen yanına t'nin kaçıncı adım olduğunu yazdırıyoruz
        std::string etiket = "t" + std::to_string(i); 
        cizim.drawText(etiket, anlikX + 0.5, anlikY + 0.5, "black", 12); 
    }

    //Bellek temizliği
    delete[] px;
    delete[] py;
    px = nullptr;
    py = nullptr;
    return 0;
}