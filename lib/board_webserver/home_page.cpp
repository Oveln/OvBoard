#include "home_page.h"
const char homepage[] ICACHE_FLASH_ATTR = R"(
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>OvBoard WiFi Setting</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f4f4f4;
                padding: 20px;
            }
            .form-container {
                background-color: #fff;
                max-width: 300px;
                margin: 0 auto;
                padding: 20px;
                box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            }
            label {
                display: block;
                margin-top: 10px;
                font-weight: bold;
            }
            input[type="text"] {
                width: 100%;
                padding: 8px;
                margin-top: 5px;
                margin-bottom: 20px;
                border: 1px solid #ccc;
                box-sizing: border-box; /* Make sure padding doesn't affect width */
            }
            input[type="submit"] {
                width: 100%;
                padding: 10px;
                background-color: #5cb85c;
                color: white;
                border: none;
                cursor: pointer;
            }
            input[type="submit"]:hover {
                background-color: #4cae4c;
            }
        </style>
    </head>
    <body>
        <div class="form-container">
            <form action="/wifi_setting" method="post">
                <label for="ssid">SSID</label><bt>
                <input type="text" id="ssid" name="ssid"><br>
                <label for="password">Password</label><bt>
                <input type="text" id="password" name="password"><br>
                <input type="submit" value="提交">
            </form>
        </div>
    </body>
</html>
)";