# 概要
盗ラれンタンを制御するための、M5Stamp Picoへのプログラムの書き込み方法について説明します。

# 必要なもの
・[M5Stamp Pico](https://www.switch-science.com/catalog/7360/)  
・[ESP32 Downloader](https://www.switch-science.com/catalog/7471/)  
・Arduino IDEがインストールされたWindows PC  
・USB Type Cケーブル  
※ M5Stamp PicoとESP32 Downloaderのセットは[こちら](https://www.switch-science.com/catalog/7361/)  

# 方法
・まずM5Stamp Picoへ書き込むbinファイルをダウンロードします。  
・適当なフォルダ (以下、フォルダ名はM5Stampと仮定)を作成し、binファイル、ArduinoIDEに付属するesptool.exeを格納する。  
・Windows PCとM5Stamp Picoを、ESP32 Downloader経由でUSB接続する。  
・Windows PCのデバイスマネージャーより、M5Stamp Picoのポート番号を確認 (以下、ポート番号はCOM3と仮定)。  
・フォルダM5Stampに、下記バッチファイル (以下、バッチファイル名はM5Stamp.binと仮定)を作成。ポート番号やファイル名は適宜修正願います。

```
set PORT=COM3
set FILE=ToLaREnternMainV1_mark1_m5stamp.ino.m5stack_stamp_pico.bin

.\esptool.exe --port %PORT% --baud 921600 --chip esp32  --before default_reset --after hard_reset ^
     write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0x10000 ./%APP%

pause
```

・下記のようなフォルダ構成となりましたら、バッチファイル(M5Stamp.bat)を実行し、M5Stamp Picoへプログラムを書き込みます。
``` 
M5Stamp/
　├ ToLaREnternMainV1_mark1_m5stamp.ino.m5stack_stamp_pico.bin
　├ esptool.exe
　└ M5Stamp.bat
``` 
