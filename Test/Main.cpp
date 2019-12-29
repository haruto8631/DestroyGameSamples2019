
# include <Siv3D.hpp> // OpenSiv3D v0.4.2


class Employee {
public:
	Employee() {
	}

	virtual void showSalary() {
		Rect(0, 0, 100, 100).draw(Color(255, 0, 0));
	}

	int salary;
};

class Salesman : Employee {
public:
	Salesman() : Employee() {
	}

	void showSalary() override {
		Employee::showSalary();
		Rect(100, 100, 200, 200).draw();
	}


};


void Main()
{
	Employee e;
	Salesman s;
	
	while (System::Update())
	{
		//e.showSalary();
		s.showSalary();
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D Slack (ユーザコミュニティ) への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
