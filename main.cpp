#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;	

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言


	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
	
	//情報を定義
	//座標
	int posX[10];
	int posY[10];
	
	//円の半径
	int radius[10];

	//円ごとの経過時間
	int timer[10];
	//このタイマーが起動状態か確認するフラグ
	bool timerActive[10];

	//次のタイマーが始まる時間
	int NextStartTime[10];
	
	//タイマーが止まる時間
	const int MaxTime = 300; //60フレーム想定で5秒間動く

	//円の半径の最大値
	const int MaxRadius = 600;

	//大きくなる速度
	const int RadiusSpeed = 3;

	//初期設定
	for (int i = 0; i < 10; i++)
	{
		//中心になるように
		posX[i] = WIN_WIDTH / 2;
		posY[i] = WIN_HEIGHT / 2;

		//0で初期化
		radius[i] = 0;
		timer[i] = 0;
		timerActive[i] = false;
	}

	//細かく設定する
	NextStartTime[0] = 10;
	NextStartTime[1] = 10;
	NextStartTime[2] = 10;
	NextStartTime[3] = 30;
	NextStartTime[4] = 30;
	NextStartTime[5] = 30;
	NextStartTime[6] = 50;
	NextStartTime[7] = 10;
	NextStartTime[8] = 90;
	NextStartTime[9] = 30;

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (keys[KEY_INPUT_SPACE])
		{
			//タイマーを初期化
			for (int i = 0; i < 10; i++)
			{
				timer[i] = 0;
				timerActive[i] = false;
			}

			//最初のタイマーを起動
			timerActive[0] = true;
		}

		//タイマーの更新
		for (int i = 0; i < 10; i++)
		{
			//iが0だと困るので除外する
			if (i != 0)
			{
				//ひとつ前の経過を見て、次のタイマーを動かす
				if (timer[i - 1] > NextStartTime[i])
				{
					timerActive[i] = true;
				}
			}

			//起動しているかを確認して
			if (timerActive[i])
			{
				//時間が最大時間にまだ達していないなら
				if (timer[i] < MaxTime)
				{
					//1フレームごとに1加算
					timer[i] += 1;
				}
			}
			//最大時間に達している場合は止まる
		}
		
		//半径の更新
		for (int i = 0; i < 10; i++)
		{
			//経過時間に合わせて大きくする
			radius[i] = timer[i] * RadiusSpeed;
		}

		// 描画処理
		
		//描画するだけ
		for (int i = 0; i < 10; i++)
		{
			DrawCircle(posX[i], posY[i], radius[i], 0xffffff, false);
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();	

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}