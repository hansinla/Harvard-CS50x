<!DOCTYPE html>

<html>

    <head>
        <title>Stock Display</title>
    </head>

    <body>
        <pre><?php
        
        print("Symbol: ".$symbol."\n");
        print("Name: ".$name."\n");
        $formattedPrice = number_format($price, 2);
        print("Price: ".$formattedPrice);
        
        
        ?></pre>
    </body>
    <a href="javascript:history.go(-1);">Back</a>
    or <a href="index.php">Home</a>

</html>
