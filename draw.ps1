Add-Type -AssemblyName System.Drawing

# ========== 画类图 ==========
$width = 900
$height = 650
$bmp = New-Object System.Drawing.Bitmap($width, $height)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.SmoothingMode = 'AntiAlias'
$g.Clear([System.Drawing.Color]::White)

$pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
$brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Black)
$fontTitle = New-Object System.Drawing.Font("Microsoft YaHei", 14, [System.Drawing.FontStyle]::Bold)
$fontClass = New-Object System.Drawing.Font("Microsoft YaHei", 11, [System.Drawing.FontStyle]::Bold)
$fontText = New-Object System.Drawing.Font("Microsoft YaHei", 9)

# 标题
$g.DrawString("生态系统模拟系统 UML 类图", $fontTitle, $brush, 280, 15)

# 画类框函数
function DrawBox($x, $y, $w, $h, $title, $lines) {
    $rect = New-Object System.Drawing.Rectangle($x, $y, $w, $h)
    $g.FillRectangle([System.Drawing.Brushes]::AliceBlue, $rect)
    $g.DrawRectangle($pen, $rect)
    $g.DrawString($title, $fontClass, $brush, $x + 8, $y + 5)
    $g.DrawLine($pen, $x, $y + 25, $x + $w, $y + 25)
    $ly = $y + 32
    foreach ($line in $lines) {
        $g.DrawString($line, $fontText, $brush, $x + 8, $ly)
        $ly += 16
    }
}

# Organism 基类
DrawBox 40 80 210 170 "Organism (生物基类)" @(
    "- alive : bool",
    "- age : int",
    "- age_max : int",
    "",
    "+ update()",
    "+ isAlive() : bool",
    "+ getX() / getY()",
    "+ foodValue()",
    "+ tryEat(other)",
    "+ name() / symbol()"
)

# Fish 类
DrawBox 340 110 190 130 "Fish (鱼类)" @(
    "- x, y : int",
    "- speed : int",
    "- energy : int",
    "",
    "+ update()",
    "+ getX() / getY()"
)

# smallFish
DrawBox 610 60 190 100 "smallFish (小鱼)" @(
    "",
    "+ update()",
    "+ foodValue() : int",
    "+ symbol() : char",
    "+ name() : string"
)

# bigFish
DrawBox 610 200 190 100 "bigFish (大鱼)" @(
    "",
    "+ update()",
    "+ tryEat(other) : bool",
    "+ symbol() : char",
    "+ name() : string"
)

# World 类
DrawBox 300 420 280 180 "World (世界/环境)" @(
    "- creatures : vector<Organism*>",
    "- dayEvents : vector<string>",
    "- day, stepInDay : int",
    "",
    "+ STEPS_PER_DAY = 3",
    "+ step() / show()",
    "+ addCreature(c)",
    "- removeDead()",
    "- reportEvents()"
)

# 连线
# Organism -> Fish (继承)
$g.DrawLine($pen, 250, 165, 340, 175)
$g.DrawString("继承", $fontText, $brush, 275, 155)

# Fish -> smallFish
$g.DrawLine($pen, 530, 140, 610, 110)
# Fish -> bigFish
$g.DrawLine($pen, 530, 180, 610, 240)

# World -> Organism (聚合)
$g.DrawLine($pen, 350, 420, 160, 250)
$g.DrawString("聚合 (1对多)", $fontText, $brush, 180, 330)

# 保存
$bmp.Save("E:\生态系统模拟系统\类图.png", [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose()
$bmp.Dispose()
Write-Output "类图.png 已生成"

# ========== 画流程图 ==========
$width = 700
$height = 850
$bmp2 = New-Object System.Drawing.Bitmap($width, $height)
$g2 = [System.Drawing.Graphics]::FromImage($bmp2)
$g2.SmoothingMode = 'AntiAlias'
$g2.Clear([System.Drawing.Color]::White)

$pen2 = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
$brush2 = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Black)
$fontBox = New-Object System.Drawing.Font("Microsoft YaHei", 10)

$g2.DrawString("World::step() 核心流程图", $fontTitle, $brush2, 200, 15)

# 画矩形节点函数
function DrawNode($g, $x, $y, $w, $h, $text) {
    $rect = New-Object System.Drawing.Rectangle($x, $y, $w, $h)
    $g.FillRectangle([System.Drawing.Brushes]::White, $rect)
    $g.DrawRectangle($pen2, $rect)
    $g.DrawString($text, $fontBox, $brush2, $x + 10, $y + 8)
}

# 画菱形判断节点
function DrawDiamond($g, $x, $y, $w, $h, $text) {
    $points = @(
        (New-Object System.Drawing.Point($x + $w/2, $y)),
        (New-Object System.Drawing.Point($x + $w, $y + $h/2)),
        (New-Object System.Drawing.Point($x + $w/2, $y + $h)),
        (New-Object System.Drawing.Point($x, $y + $h/2))
    )
    $g.FillPolygon([System.Drawing.Brushes]::White, $points)
    $g.DrawPolygon($pen2, $points)
    $g.DrawString($text, $fontBox, $brush2, $x + 20, $y + 10)
}

# 开始
DrawNode $g2 280 50 120 40 "开始 step()"
# 箭头
$g2.DrawLine($pen2, 340, 90, 340, 110)

# 遍历生物
DrawNode $g2 230 110 220 40 "遍历所有生物，调用 update()"
$g2.DrawLine($pen2, 340, 150, 340, 170)

# 判断
DrawDiamond $g2 250 170 180 60 "update 后是否死亡?"
# 是 -> 记录事件
$g2.DrawLine($pen2, 430, 200, 500, 200)
DrawNode $g2 500 180 160 40 "记录: XX 死亡"
$g2.DrawLine($pen2, 580, 220, 580, 280)
$g2.DrawLine($pen2, 580, 280, 340, 280)

# 否 -> 捕食判定
$g2.DrawLine($pen2, 340, 230, 340, 280)

DrawNode $g2 220 280 240 40 "遍历捕食者，判定 tryEat()"
$g2.DrawLine($pen2, 340, 320, 340, 340)

DrawDiamond $g2 260 340 160 60 "捕食成功?"
# 是
$g2.DrawLine($pen2, 420, 370, 500, 370)
DrawNode $g2 500 350 160 40 "记录: 大鱼吃小鱼"
$g2.DrawLine($pen2, 580, 390, 580, 440)
$g2.DrawLine($pen2, 580, 440, 340, 440)
# 否
$g2.DrawLine($pen2, 340, 400, 340, 440)

DrawNode $g2 230 440 220 40 "removeDead() 清理死亡生物"
$g2.DrawLine($pen2, 340, 480, 340, 500)

DrawNode $g2 230 500 220 40 "reportEvents() 播报事件"
$g2.DrawLine($pen2, 340, 540, 340, 560)

DrawDiamond $g2 240 560 200 60 "走满 3 步 (一天结束)?"
# 是
$g2.DrawLine($pen2, 440, 590, 520, 590)
DrawNode $g2 520 570 150 40 "show() 打印地图"
$g2.DrawLine($pen2, 595, 610, 595, 660)
$g2.DrawLine($pen2, 595, 660, 340, 660)
# 否
$g2.DrawLine($pen2, 340, 620, 340, 660)

# 结束
DrawNode $g2 280 660 120 40 "结束本次 step"

# 保存
$bmp2.Save("E:\生态系统模拟系统\流程图.png", [System.Drawing.Imaging.ImageFormat]::Png)
$g2.Dispose()
$bmp2.Dispose()
Write-Output "流程图.png 已生成"
