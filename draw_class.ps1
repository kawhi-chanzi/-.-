Add-Type -AssemblyName System.Drawing

# ========== 类图 ==========
$bmp = New-Object System.Drawing.Bitmap(850, 600)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.SmoothingMode = 'AntiAlias'
$g.Clear([System.Drawing.Color]::White)

$pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
$brush = [System.Drawing.Brushes]::Black
$fontTitle = New-Object System.Drawing.Font("Microsoft YaHei", 14, [System.Drawing.FontStyle]::Bold)
$fontClass = New-Object System.Drawing.Font("Microsoft YaHei", 11, [System.Drawing.FontStyle]::Bold)
$fontText = New-Object System.Drawing.Font("Microsoft YaHei", 9)

$g.DrawString("生态系统模拟系统 UML 类图", $fontTitle, $brush, 250, 15)

# Organism
$g.FillRectangle([System.Drawing.Brushes]::AliceBlue, 40, 70, 200, 160)
$g.DrawRectangle($pen, 40, 70, 200, 160)
$g.DrawString("Organism 生物基类", $fontClass, $brush, 50, 75)
$g.DrawLine($pen, 40, 98, 240, 98)
$g.DrawString("- alive, age, age_max", $fontText, $brush, 50, 105)
$g.DrawString("", $fontText, $brush, 50, 121)
$g.DrawString("+ update()", $fontText, $brush, 50, 137)
$g.DrawString("+ isAlive()", $fontText, $brush, 50, 153)
$g.DrawString("+ getX() / getY()", $fontText, $brush, 50, 169)
$g.DrawString("+ foodValue()", $fontText, $brush, 50, 185)
$g.DrawString("+ tryEat(other)", $fontText, $brush, 50, 201)
$g.DrawString("+ name() / symbol()", $fontText, $brush, 50, 217)

# Fish
$g.FillRectangle([System.Drawing.Brushes]::AliceBlue, 320, 100, 180, 120)
$g.DrawRectangle($pen, 320, 100, 180, 120)
$g.DrawString("Fish 鱼类", $fontClass, $brush, 330, 105)
$g.DrawLine($pen, 320, 128, 500, 128)
$g.DrawString("- x, y, speed, energy", $fontText, $brush, 330, 135)
$g.DrawString("", $fontText, $brush, 330, 151)
$g.DrawString("+ update()", $fontText, $brush, 330, 167)
$g.DrawString("+ getX() / getY()", $fontText, $brush, 330, 183)

# smallFish
$g.FillRectangle([System.Drawing.Brushes]::AliceBlue, 590, 50, 180, 100)
$g.DrawRectangle($pen, 590, 50, 180, 100)
$g.DrawString("smallFish 小鱼", $fontClass, $brush, 600, 55)
$g.DrawLine($pen, 590, 78, 770, 78)
$g.DrawString("+ update()", $fontText, $brush, 600, 85)
$g.DrawString("+ foodValue() = 3", $fontText, $brush, 600, 101)
$g.DrawString("+ symbol() = 's'", $fontText, $brush, 600, 117)
$g.DrawString("+ name() = '小鱼'", $fontText, $brush, 600, 133)

# bigFish
$g.FillRectangle([System.Drawing.Brushes]::AliceBlue, 590, 180, 180, 100)
$g.DrawRectangle($pen, 590, 180, 180, 100)
$g.DrawString("bigFish 大鱼", $fontClass, $brush, 600, 185)
$g.DrawLine($pen, 590, 208, 770, 208)
$g.DrawString("+ update()", $fontText, $brush, 600, 215)
$g.DrawString("+ tryEat(other)", $fontText, $brush, 600, 231)
$g.DrawString("+ symbol() = 'B'", $fontText, $brush, 600, 247)
$g.DrawString("+ name() = '大鱼'", $fontText, $brush, 600, 263)

# World
$g.FillRectangle([System.Drawing.Brushes]::AliceBlue, 260, 360, 260, 180)
$g.DrawRectangle($pen, 260, 360, 260, 180)
$g.DrawString("World 世界/环境", $fontClass, $brush, 270, 365)
$g.DrawLine($pen, 260, 388, 520, 388)
$g.DrawString("- creatures: vector<Organism*>", $fontText, $brush, 270, 395)
$g.DrawString("- dayEvents: vector<string>", $fontText, $brush, 270, 411)
$g.DrawString("- day, stepInDay: int", $fontText, $brush, 270, 427)
$g.DrawString("", $fontText, $brush, 270, 443)
$g.DrawString("+ step() / show()", $fontText, $brush, 270, 459)
$g.DrawString("+ addCreature(c)", $fontText, $brush, 270, 475)
$g.DrawString("- removeDead()", $fontText, $brush, 270, 491)
$g.DrawString("- reportEvents()", $fontText, $brush, 270, 507)

# 连线
$g.DrawLine($pen, 240, 150, 320, 160)  # Organism -> Fish
$g.DrawString("继承", $fontText, $brush, 260, 140)

$g.DrawLine($pen, 500, 130, 590, 100)  # Fish -> smallFish
$g.DrawLine($pen, 500, 170, 590, 220)  # Fish -> bigFish

$g.DrawLine($pen, 320, 360, 140, 230)  # World -> Organism
$g.DrawString("聚合 1对多", $fontText, $brush, 160, 290)

$bmp.Save("E:\生态系统模拟系统\class_diagram.png", [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose()
$bmp.Dispose()
Write-Output "类图 OK"
