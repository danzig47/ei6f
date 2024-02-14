<?php

    //タイムゾーン設定
    //date_default_timezone_set('Asia/Tokyo');
    $today = date("Y-m-d");

    //データベースに接続するための宣言
    $db = new SQLite3('../env_ei6f.db');

    //結果を取得
    $res = $db->query('SELECT date, time, co2 FROM env where date >= "2021-05-24"');

    $data = array();
    // Fetch Associated Array (1 for SQLITE3_ASSOC)
    while ($r= $res->fetchArray(SQLITE3_ASSOC)) {
        array_push($data, $r);
    }

    $db->close();

    //you can return a JSON array
 //   echo json_encode($data, JSON_UNESCAPED_UNICODE|JSON_PRETTY_PRINT);
    echo json_encode($data);

?>
