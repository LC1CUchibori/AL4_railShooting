#ifndef PLCHUNEFFECT_H
#define PLCHUNEFFECT_H

#include "Vector2.h" // 必要ならVector2のヘッダをインクルード（位置管理用）

struct Color {
    int r, g, b;

    Color() : r(255), g(255), b(255) {} // デフォルトで白
    Color(int r, int g, int b) : r(r), g(g), b(b) {}
};


// プチュンエフェクトクラス
class PlchunEffect {
public:
    // コンストラクタと初期化
    PlchunEffect();
    void Initialize();

    // エフェクトの更新
    void Update();

    // エフェクトの描画
    void Draw();

    // スペースキーでエフェクトを発動
    void Trigger();

    // 円を描画する関数
    void DrawCircle(float x, float y, float radius, Color color);

private:
    bool isActive_;      // エフェクトがアクティブかどうか
    float scale_;        // 現在のスケール
    const float maxScale_; // 最大スケール
    const float scaleSpeed_; // スケールの変化速度
    Vector2 position_;   // エフェクトの位置
    Color color_;        // エフェクトの色（白色として初期化）

};

#endif // PLCHUNEFFECT_H
