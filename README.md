# 42cursus

このリポジトリは、エンジニア養成スクール42Tokyoでの学習記録です。  
42Tokyoとは、教師不在のプログラミングスクールで、生徒同士の教え合いや相互レビューによって運営される学校です。  
入学には4週間に渡る厳しい試験があることと、入学後も課題を期限までにパスしなければ除籍処分されてしまうことが特徴です。

入学試験中の課題については規約により公開できないため、このリポジトリは本科入学後のみの内容となります。

2020/11/2に42Tokyo本科に入学してから取り組んできた課題の一覧です。
```
libft         : 標準ライブラリlibcを再実装しました。atoiやstrlcpy等、40以上の関数を含むライブラリです。
get_next_line : 指定したファイルの一行分を取得する関数を作成しました。2回目にこの関数が呼ばれたら、2行目を取得します。
ft_printf     : printfを再実装しました。文字列,10進数,16進数,アドレスの出力や、幅等のフォーマットも再現しました。
ft_mini_ls    : カレントディレクトリの一覧を表示する"ls"コマンドを再現しました。
exam02        : オフラインの試験対策です。先述のget_next_line,ft_printf等の問題からランダムで出題されます。
ft_server     : Dockerを用いて、nginx/wordpress/phpmyadminが動作する環境を構築しました。
cub3d         : 一人称視点の3dゲームを作成しました。壁や敵の配置等の情報が記述されたファイルを読み込み、描画します。
exam03        : オフラインの試験対策です。ファイルから情報を読み込み、標準出力で長方形や円を出力します。
ft_services   : Docker,kubernetesを用いてクラスタを作成します。ft_serverの要件+各ポッド監視等を行います。
```

以下は、上記課題から一部抜粋して実際の動作画面と課題の詳細を紹介します。

***

## "ft_printf"
![demo](https://raw.githubusercontent.com/wiki/kotosanagi/42cursus/images/ft_printf_demo.png)

<details>
<summary>テストファイルの詳細(クリックでオープン)</summary>
<pre>
<code>
// gcc -Wall -Wextra -Werror main.c ./libftprintf.a && ./a.out
#include "./ft_printf.h"
#include <stdio.h>
int main()
{
    int x, y;    
   
    x = ft_printf("ft:[%4s]", "koto");
    printf("\n");
    y = printf("og:[%4s]", "koto");
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);
    
    x = ft_printf("ft:[%6s]", "koto");
    printf("\n");
    y = printf("og:[%6s]", "koto");
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%2d]", 200);
    printf("\n");
    y = printf("og:[%2d]", 200);
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%x]", 200);
    printf("\n");
    y = printf("og:[%x]", 200);
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%-4X]", 200);
    printf("\n");
    y = printf("og:[%-4X]", 200);
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%20p]", "koto");
    printf("\n");
    y = printf("og:[%20p]", "koto");
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%*s]",-4, "koto");
    printf("\n");
    y = printf("og:[%*s]",-4, "koto");
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    x = ft_printf("ft:[%d %s %x]", 54, "koto", 1234567);
    printf("\n");
    y = printf("og:[%d %s %x]", 54, "koto", 1234567);
    printf("\nft ret : %d\n", x-5);
    printf("og ret : %d\n\n", y-5);

    return 0;
}
</code>
</pre>
</details>


C言語を用いて、ライブラリ関数のprintfの機能の一部を再現しました。  
makeコマンドでアーカイブファイル「libftprintf.a」が生成されます。  
実行時にこのファイルと、ヘッダーファイルに「ft_printf.h」を含めてコンパイルすることで、本自作関数が使えます。  
使用可能な関数はwriteやmalloc、freeやva_arg等に限られています。

今回自作したprintfの仕様は以下の通りです。
```
%[フラグ][最小フィールド幅].[精度][変換指定子]

--備考--
フラグ    :-0.*
変換指定子:cspdiuxX%
長さ指定子:未対応
返り値    :本家通り、出力した文字数(int)
--------
```

printf関数は、以下のように呼び出す度に引数の数が異なることがあるので、va_arg関数を用いて対応しました。
```c
printf("Hello World\n");                 // Hello World
printf("%4d年%2d月%2d日\n", 2021, 5, 9); // 2021年05月09日
```

数値の出力を行うd,i,u,x,X,pの変換指定子の処理は、共通している部分は切り出して、各処理に進数の数と各数字の文字列を与えています。

出力の文字数等の管理を行う最小フィールド幅と精度については、出力する文字数等をあらかじめ計算し、指定された値と比較して出力文字数を決定します。  
また返り値については文字を出力する度にカウントし、終了時に返却するようにしています。

***

## "cub3D"
![demo](https://raw.githubusercontent.com/wiki/kotosanagi/42cursus/images/cub3D_demo.gif)

C言語を用いて、一人称視点のゲームを作成する課題です。  
使用できるライブラリは、以下のような機能に限られています。
```
・ウィンドウの表示
・各ピクセルに指定したrgb情報の色を表示する
・ウィンドウを閉じる、等のイベント管理
```
makeコマンドで実行ファイル「cub3d」が生成されます。  
実行には以下のように、マップ情報が記述されたファイルのパスを引数として与えると、この情報をもとにゲーム画面のレンダリングを行います。
```
./cub3d maps/koto.cub
```
マップファイルの情報は、以下のようなフォーマットで与えます。
```
R 400 300
EA images/koto_east.xpm
WE images/koto_west.xpm
SO images/koto_south.xpm
NO images/koto_north.xpm
S images/koto_sprite.xpm
C 0,204,255
F 0,204,51

1111111111
1220N 0 01
100200020111111111
100002000        1
100200020111111111
1000020001
1111111111
```
それぞれのマップの要素が示す意味は、以下の通りです。
```
R            :プレイ画面の、ウィンドウの幅と高さを指定します。
EA,WE,SO,NO,S:東西南北の壁、敵のテクスチャの画像パスを指定します。
C,F          :空と床の色をrgbで指定します。
マップ部     :1は壁、2は敵、0か半角スペースは通常の床です。プレイヤーの初期位置はE,W,S,Nのいずれかで指定します。
```


fscanf等のライブラリ関数の使用は禁止されているため、前述した自作関数ライブラリlibftや、get_next_line関数を使用して読み込み処理を行いました。  
また上記それぞれの条件について、要件に満たない情報が与えられた場合にはエラーメッセージを返し、正常に終了させます。

描画については、レイトレーシングの手法を用いて実装しました。  
遠いオブジェクトは小さく、近いオブジェクトは大きく描画するため、プレイヤーの位置ベクトル情報、視線ベクトル情報等をもとに、壁や敵までの距離を計算します。  
読み込んだテクスチャの画像パスから、各ピクセルに表示する色情報を指定し、連続的に描画します。

※このプログラムは、以下の環境で動作確認済みです。
```
Ubuntu 18.04.5 LTS
```
