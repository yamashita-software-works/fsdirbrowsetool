# FSDirBrowseTool
 
Version 0.1 Preview

指定されたディレクトリに含まれるファイルの情報を表示するアプリケーションです。

古いWDKとSDKのみを使ってWindowsのネイティブAPIを使用するWin32アプリケーションを作成方法を残すために、利用可能なソースコードを寄せ集め、整理したものを公開しています。
現状では実用的なアプリケーションというより、WDKを使用して作成するWin32 GUIアプリケーション作成のひな形（サンプルアプリケーション）という位置づけです。

そのため、表示されるファイル情報は初歩的なもののみで、最低限の実装となっています。ディレクトリを指定したり、他のボリュームへ切り替えるUIさえありません。今後徐々に追加する予定です。

**このアプリケーションは開発中のため、現状の仕様，機能，構成，UIデザイン，ファイル名，ビルド構成などは常に変更されます。**

<br>

## 使い方

1. wfsdirbrowse.exeを実行します。

1. メニューの `File > New` を選択します。

カレントディレクトリの内容が表示されます。現状ではUIによる場所の指定方法を提供していない為、開いた場所と同じボリューム内のディレクトリ間のみ移動できます。

直接場所を指定するには、コマンドライン引数を利用します。

以下は、起動時に Windowsディレクトリと HarddiskVolume1のルート 及び HarddiskVolume2\foo を開く例です。


    wfsdirbrowse C:\windows \Device\HarddsikVolume1\ \??\HarddiskVolume2\foo

<br>

## Build

### 開発環境
ソースからビルドするには　Windows Driver Kit Version 7.1.0 (WDK) と Windows SDK for Windows 7 and .NET Framework 4 (Veriosn 7.1)が必要です。

https://www.microsoft.com/en-us/download/details.aspx?id=11800

https://www.microsoft.com/en-us/download/details.aspx?id=8442

>ISOファイルを使ってSDKをインストールする場合、プラットフォームごとに異なるので注意してください。   
>64bit環境にインストールする時は GRMSDKX_EN_DVD.iso を、
>32bit環境にインストールする時は GRMSDK_EN_DVD.iso をダウンロードしてください。
>適合しないファイルを使用するとエラーとなりインストールできません。



現在のビルド環境は、上記WDKとSDKが以下の場所にインストールされている前提になっています。WDKはデフォルトで下記の場所になっていますが、SDKのデフォルトは異なっているので注意してください。

WDK   
`C:\WinDDK\7600.16385.1`

SDK   
`C:\WinSDK\7.1`

もし別の場所にインストールされている場合は、その場所へのリンクを持つ上記パスと同じ名前のジャンクションポイントをC:ドライブのルートに作成すると便利です。

例)
`C:\WinSDK\7.1 -> C:\Program Files\Microsoft SDKs\v7.1`

>**Warning**   
>現状、ビルドに使用するsourcesファイル内に記述されたWDK/SDKルートパスがハードコードされているためです。
>独自のインストール先を設定したい場合は、sourcesファイルを編集して当該パスを調整する必要があります。
>編集する場合、sourcesファイルに記述するパスにはスペースを含めないでください。

> **Note**   
>SDKのセットアップは、マウントされた(またはCD/DVD)ドライブのルートにあるsetup.exeではなく、Setupフォルダ下のSDKSetup.exe を実行してください。   
> `\Setup\SDKSetup.exe`
>
>
>もしインストール時にエラーが発生した場合は、以下のVS2010再頒布モジュールをアンインストールしてから再度試してみてください。
>
>`Microsoft Visial C++ 2010 x86 Redistributable - 10.0.xxxxx`   
>`Microsoft Visial C++ 2010 x64 Redistributable - 10.0.xxxxx`

> **Note**   
>SDKから最低限必要なものは、ヘッダファイルとライブラリファイルのみです。コンパイラやツールは不要です。


<br>

### ビルド方法
スタートメニューの以下の項目を開きます。

`Windows Driver Kits > WDK 7600.16385.1 > Build Environments>Windows 7`

から

64ビット版をビルドする場合は、`x64 Free Build Environment`

32ビット版をビルドする場合は、 `x86 Free Build Environment`

のどちらかを開きます。

> **Warning**   
Windows 10ではスタートメニュー(Windows Driver Kits)から適切な開発環境を選べない場合があります（シェルリンク名が同じであるため）。
正しく選択できない場合は、シェルリンクがあるスタートアップメニューのフォルダを開いて直接選択してください。

<br>
コマンドプロンプトが開くので、ソースの展開先ディレクトリへ移動して、以下のbuildコマンドを実行します。
<br>
<br>

    build -c

最初のビルドでは以下のオプションをお勧めします。

    build -c -M 1



## License

Copyright (C) YAMASHITA Katsuhiro. All rights reserved.

Licensed under the [MIT](LICENSE) License.
