## シンプルなSTGゲーム
このゲームは『スペースインベーダー』のような固定画面シューティングゲーム。

## プレイ方法
「Space」キーを押して弾を撃って、全てのエネミーを撃破する。エネミーが画面最下部まで降りてきたらまたエネミーが飛行機にぶつかったらゲームオーバーとなる。

## 開発環境
* OS: Linux(Ubuntu 20.04)
* プログラミング言語: C++
* IDE: Visual Studio Code
* 外部ライブラリ
	* [OpenCV v4.5.5](https://opencv.org/)
	* [GLFW(OpenGLライブラリのひとつ) v3.4](https://www.glfw.org/)
	* [Glad](https://glad.dav1d.de/)
* ゲームエンジン: [OpenGLとOpenCVライブラリに基づく自作ゲームエンジン](./GameLib2D.cpp)

## コンパイルとリンク
このプロジェクトはLinux環境で開発されたが、Windows環境でのコンパイルとリンクも可能です。
### [cmake](https://cmake.org/)とmakeコマンドでプログラムを作成する(Linux利用者向け)
cd ${path of the project} <br />cmake .  <br />make  以上のコマンドを実行すると、Linuxの実行ファイルが作成される。

### Visual Studioでプログラムを作成する(Windows利用者向け)
外部ライブラリのパスを指定すると、Visual Studioでプログラムを作成することも可能です。

## 自作ゲームエンジンの原理
本プロジェクトは最終画面をテクスチャにしてOpenGLコマンドでレンダリングする。

## 参考資料
*  [Learn OpenGL](https://learnopengl.com/)
* 「最短距離でゼロからしっかり学ぶ Python入門 実践編 〜ゲーム開発・データ可視化・Web開発」
* 「ゲームプログラマになる前に覚えておきたい技術」
* 「Fundamentals Of Computer Graphics」

## プログラムの開発者
glad.c、[4.1.texture.vs](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.1.textures/4.1.texture.fs)、[4.1.texture.fs](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.1.textures/4.1.texture.fs)と[shader.hpp](https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h)以外のソースコードは、全部私が開発したものです。