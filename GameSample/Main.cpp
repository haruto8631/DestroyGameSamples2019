# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "Result.hpp"



void Main()
{
	// タイトルを設定
	Window::SetTitle(U"破壊ゲームさんぷる");

	// 背景色を設定
	Scene::SetBackground(Color(0, 0, 0));

	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 60, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");
	FontAsset::Register(U"Score", 30, Typeface::Regular);


	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.add<Result>(State::Result)
		.setFadeColor(Color(0, 0, 0));

	// タイトルシーンから始めるように設定する
	manager.init(State::Title);

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
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
