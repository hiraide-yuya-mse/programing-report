//
//  main.cpp
//  プログラミング演習　最終課題
//
//  Created by 平出雄哉 on 2020/08/09.
//  Copyright © 2020 平出雄哉. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>//円周率を利用できるライブラリを導入

using namespace std;

class Moment {
    float b, h, d1, d2;//幅(底辺)，高さ，外径，内径
    
public:
    //nameとmomentは後で並び替えを行うために外部からのアクセスが可能なpublicへ。
    string name;
    float moment;
    
    //それぞれのデータメンバを変更するメンバ関数。
    void setName ( const string& newname ) { name = newname; };
    void setB ( const float& newb ) { b = newb; };
    void setH ( const float& newh ) { h = newh; };
    void setD1 ( const float& newd1 ) { d1 = newd1; };
    void setD2 ( const float& newd2 ) { d2 = newd2; };
    void setMoment ( const float& newMoment ) { moment = newMoment; };
    
     //それぞれの断面二次モーメントの情報を画面に出力するメンバ関数。
    void show_square(){
        cout << "幅が" << b << "[m],"<< "高さが" << h << "[m]の長方形断面の断面二次モーメントは, " << moment << "[m^4]です。" << endl << endl;
    };
    void show_triangle(){
        cout << "底辺が" << b << "[m],"<< "高さが" << h << "[m]の二等辺三角形断面の断面二次モーメントは, " << moment << "[m^4]です。" << endl << endl;
    };
    void show_round(){
        cout << "直径が" << d1 << "[m]の円形断面の断面二次モーメントは, " << moment << "[m^4]です。" << endl << endl;
    };
    void show_ring(){
        cout << "外径が" << d1 << "[m],"<< "内径が" << d2 << "[m]の中空円断面の断面二次モーメントは, " << moment << "[m^4]です。" << endl << endl;
    };
    void show_moment(){
        cout << moment << endl;
    };
};

bool operator<(const Moment& lhs, const Moment& rhs) {
    return lhs.moment < rhs.moment;
}

//断面に次モーメントを計算する関数
auto calculator_of_square (float b_cal, float h_cal) {
    return (b_cal * pow(h_cal, 3.0))/12.0;
}

auto calculator_of_triangle (float b_cal, float h_cal) {
    return (b_cal * pow(h_cal, 3.0))/36.0;
}

auto calculator_of_round (float d1_cal) {
    return (M_PI * pow(d1_cal, 4.0))/64.0;
}

auto calculator_of_ring (float d1_cal, float d2_cal) {
    return (M_PI * (pow(d1_cal, 4.0) - pow(d2_cal, 4.0)))/64.0;
}


int main () {
    //計算する断面二次モーメントの数を入力。
    int Num_of_Moment;
    cout << "計算する断面二次モーメントの数を入力してください。" << endl;
    cin >> Num_of_Moment;
    
    //クラスMomentのvector vを定義。
    vector<Moment> v;
    
    //上で入力した回数だけ以降の処理を繰り返す。
    int x = 0;
    while (x < Num_of_Moment) {//for (int x = 1 ;  x <= Num_of_Moment ; x++) {
        //断面の図形を選択
        int Type_of_Moment;
        cout << x+1 << "つ目の断面の形状を次から選択してください。" << endl;
        cout << "1:長方形 2:二等辺三角形 3:円形 4:中空円" << endl;
        cin >> Type_of_Moment;
        
        //それぞれの断面の図形に対し処理を場合分け。
        //入力された情報と関数を使って計算した断面二次モーメントの情報をクラスMomentに格納。また、画面に出力。
        if (Type_of_Moment == 1){
            v.emplace_back();
            v[x].setName("長方形");
            float b_in, h_in;
            cout << x+1 << "つ目の長方形の幅と高さを入力してください。単位は[m]です。" << endl;
            cin >> b_in;
            v[x].setB(b_in);
            cin >> h_in;
            v[x].setH(h_in);
            
            float Moment_Square = calculator_of_square(b_in, h_in);
            v[x].setMoment(Moment_Square);
            v[x].show_square();
        }
        
        if (Type_of_Moment == 2){
            v.emplace_back();
            v[x].setName("二等辺三角形");
            float b_in, h_in;
            cout << x+1 << "つ目の二等辺三角形の底辺と高さを入力してください。単位は[m]です。" << endl;
            cin >> b_in;
            v[x].setB(b_in);
            cin >> h_in;
            v[x].setH(h_in);
            
            float Moment_Triangle = calculator_of_triangle(b_in, h_in);
            v[x].setMoment(Moment_Triangle);
            v[x].show_triangle();
        }
        
        if (Type_of_Moment == 3){
            v.emplace_back();
            v[x].setName("円形");
            float d1_in;
            cout << x+1 << "つ目の円型断面の直径を入力してください。単位は[m]です。" << endl;
            cin >> d1_in;
            v[x].setD1(d1_in);
            
            float Moment_Round = calculator_of_round(d1_in);
            v[x].setMoment(Moment_Round);
            v[x].show_round();
        }
        
        if (Type_of_Moment == 4){
            v.emplace_back();
            v[x].setName("中空円");
            float d1_in, d2_in;
            cout << x+1 << "つ目の円形断面の外径と内径を入力してください。単位は[m]です。" << endl;
            cin >> d1_in;
            v[x].setD1(d1_in);
            cin >> d2_in;
            v[x].setD2(d2_in);
            
            float Moment_Ring = calculator_of_ring(d1_in, d2_in);
            v[x].setMoment(Moment_Ring);
            v[x].show_ring();
        }
        
        x++;
    }
    //クラスに格納したmomentの値の小さい順に並べ替えて画面に出力。
    sort(v.begin(), v.end());
    cout << "小さい順に並べると、" << endl;
    for (auto& p : v) cout << p.name << "(" << p.moment << "[m^4]), ";
    cout << "です。" << endl;
}



