<?php
/**
 * WordPress の基本設定
 *
 * このファイルは、インストール時に wp-config.php 作成ウィザードが利用します。
 * ウィザードを介さずにこのファイルを "wp-config.php" という名前でコピーして
 * 直接編集して値を入力してもかまいません。
 *
 * このファイルは、以下の設定を含みます。
 *
 * * MySQL 設定
 * * 秘密鍵
 * * データベーステーブル接頭辞
 * * ABSPATH
 *
 * @link https://ja.wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// 注意:
// Windows の "メモ帳" でこのファイルを編集しないでください !
// 問題なく使えるテキストエディタ
// (http://wpdocs.osdn.jp/%E7%94%A8%E8%AA%9E%E9%9B%86#.E3.83.86.E3.82.AD.E3.82.B9.E3.83.88.E3.82.A8.E3.83.87.E3.82.A3.E3.82.BF 参照)
// を使用し、必ず UTF-8 の BOM なし (UTF-8N) で保存してください。

// ** MySQL 設定 - この情報はホスティング先から入手してください。 ** //
/** WordPress のためのデータベース名 */
define( 'DB_NAME', 'dbname' );

/** MySQL データベースのユーザー名 */
define( 'DB_USER', 'user' );

/** MySQL データベースのパスワード */
define( 'DB_PASSWORD', 'pass' );

/** MySQL のホスト名 */
define( 'DB_HOST', 'localhost' );

/** データベースのテーブルを作成する際のデータベースの文字セット */
define( 'DB_CHARSET', 'utf8' );

/** データベースの照合順序 (ほとんどの場合変更する必要はありません) */
define( 'DB_COLLATE', '' );

/**#@+
 * 認証用ユニークキー
 *
 * それぞれを異なるユニーク (一意) な文字列に変更してください。
 * {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org の秘密鍵サービス} で自動生成することもできます。
 * 後でいつでも変更して、既存のすべての cookie を無効にできます。これにより、すべてのユーザーを強制的に再ログインさせることになります。
 *
 * @since 2.6.0
 */

define('AUTH_KEY',         '!8)T,`$,1#s&7=d5@^EXBn~)+$rgo2gHMzv|oU$/fk6=)Tr7l7)(BvK~U4gkJ^eh');
define('SECURE_AUTH_KEY',  '[((b.8A&3_5!3 ZZe-kBtYyz[yLr[ncM[ 8:K%BD~`>>-=G<K4o8-<PbVm|60%;[');
define('LOGGED_IN_KEY',    '^GMAZHucT{J_wbt1juY7Xsy3Lg)*1(cV2$5}#l8!XH?aTtdQ?0:pBc/mJ_Tj**cJ');
define('NONCE_KEY',        '?0|R+Vr(DZ2cIRz>kv!nH!m38T4)ZU!0}b( uKM26@&{2+H~r*6k8qs8u0FH6c.K');
define('AUTH_SALT',        'WkGDPfTDOtB&*9kcIK(LZe3d+O6/&-k#sTZ+AsB:)7X!2N$_c}_KO3c)O1W8ZLW8');
define('SECURE_AUTH_SALT', '}/CR-],CfAgp*-cRt3>&pGmJD=w|@ip?)wD?Oij]7i&-pbs-tg|-V)E-#+kHaHz&');
define('LOGGED_IN_SALT',   'dE=c98Zv?4wc>EZ+(*+Eg25//!07L=Lkrf-2k> ;~-D7BCi_;jh ?tzqA7&a*$&=');
define('NONCE_SALT',       '48b-a/l8nhHIsp8OOx1J%nO[ZiZS;pupd[|G4:Ak6[;mUwi;DtJOq6]RKkBX7]8x');

/**#@-*/

/**
 * WordPress データベーステーブルの接頭辞
 *
 * それぞれにユニーク (一意) な接頭辞を与えることで一つのデータベースに複数の WordPress を
 * インストールすることができます。半角英数字と下線のみを使用してください。
 */
$table_prefix = 'wp_';

/**
 * 開発者へ: WordPress デバッグモード
 *
 * この値を true にすると、開発中に注意 (notice) を表示します。
 * テーマおよびプラグインの開発者には、その開発環境においてこの WP_DEBUG を使用することを強く推奨します。
 *
 * その他のデバッグに利用できる定数についてはドキュメンテーションをご覧ください。
 *
 * @link https://ja.wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* 編集が必要なのはここまでです ! WordPress でのパブリッシングをお楽しみください。 */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
        define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';