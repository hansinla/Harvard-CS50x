<?php

    // configuration
    require("../includes/config.php");
    
    $result = query("SELECT * from stock WHERE id = ?", $_SESSION["id"]);
    if ($result === false)
    {
        apologize("Sorry, something went wrong");
    }
    else
    {
        //dump($result);
        $positions = [];
        foreach ($result as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
        }
        $cashholding = query("SELECT cash from users WHERE id = ?", $_SESSION["id"]);
        $cash = number_format($cashholding[0]["cash"], 2);
        // render portfolio
        render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash" => $cash ]);
    }

?>
