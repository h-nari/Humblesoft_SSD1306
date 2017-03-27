# Humblesoft_SSD1306
arduino library for SSD1306, inherit Adafruit_SSD1306 add Kanji drawing feature

SSD1306コントローラを用いたOLED用Arduino library

## 概要

* SPI接続のみサポート
* Adafruit_GFXクラス継承, 直線、図形、文字描画機能
* Humblesoft_GFXクラス継承、 日本語(fontx)描画機能
* Adafruit_SSD1306ほぼコンパチ

## スケッチの例(examples)の説明

### scrollText_example

<img hspace="20" src="https://github.com/h-nari/Humblesoft_SSD1306/blob/master/img/170327a5.jpg?raw=true" width="320" align="right">
* 文字のスクロール表示機能(ScrollTextクラス)のデモ
* スクロール速度を変えて表示
 * dps = dot per second
* 動画: <a href="https://youtu.be/_Fvh-PVP-tY">YouTube</a>
<br clear="right"/>

### kanjiDisp

<img hspace="20" src="https://github.com/h-nari/Humblesoft_SSD1306/blob/master/img/170127a1.jpg?raw=true" width="320" align="right">
* 日本語表示のデモ
* 日本語フォント(fontx)は #include で読み込み
* プログラムサイズが大きくなるためOTA(Over The Air, WiFi経由のプログラム書込み)は使用不可
<br clear="right"/>


### kanjiDisp_SPIFFS_OTA
<img hspace="20" src="https://github.com/h-nari/Humblesoft_SSD1306/blob/master/img/170127a3.jpg?raw=true" width="320" align="right">
* 日本語表示 + OTA の例
* 日本語フォント(fontx)をesp8266 arduinoのfile systemに格納
  * 事前に書き込む必要有
   * (参考:[ESP8266FSインストール方法](http://www.humblesoft.com/wiki/?ESP8266FS%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB%E6%96%B9%E6%B3%95 "ESP8266FSインストール方法"))
* プログラムサイズが小さくなるのでOTA使用可能
* conf.h-sampleをconf.hにコピーし、自分の環境に合わせて設定してください


<br clear="right"/>

### textDisp
<img hspace="20" src="https://github.com/h-nari/Humblesoft_SSD1306/blob/master/img/170127a4.jpg?raw=true" width="320" align="right">
* 文字表示のデモ
<br clear="right"/>

## 元にさせて頂いたライブラリ/記事

* Adafruit_SSD1306
* I2C 極小 OLED（ 有機EL ) SSD1306 を Arduino でライブラリを使わずに動作させてみました](https://www.mgo-tec.com/blog-entry-31.html "I2C 極小 OLED（ 有機EL ) SSD1306 を Arduino でライブラリを使わずに動作させてみました")

## 変更履歴

### 2017/03/27(Mon)

* scrollTextクラスを追加
* examplesにscrollText_exampleを追加
