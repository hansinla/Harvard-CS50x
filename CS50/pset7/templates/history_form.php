<style>
#stocktable
{
    font-family:"Trebuchet MS", Arial, Helvetica, sans-serif;
    width:60%;
    border-collapse:collapse;
    margin-left: auto;
    margin-right: auto;
}
#stocktable td, #stocktable th 
{
    font-size:1em;
    text-align:left;
    border:1px solid #A0A0A0;
    padding:3px 7px 2px 7px;
}
#stocktable th 
{
    font-size:1.1em;
    text-align:center;
    padding-top:5px;
    padding-bottom:4px;
    background-color:#A0A0A0;
    color:#ffffff;
}
#stocktable tr
{
    background-color:#E5E5E5;
}
#stocktable tr td.alt
{
    text-align:right;
}
</style>

<table id="stocktable">
<tr>
    <th>Date/Time</th>
    <th>Symbol</th>
    <th>Name</th>
    <th>Buy/Sell</th>		
    <th>Shares</th>
    <th>Price</th>
</tr>

<?php foreach ($positions as $position): ?>
    
    <tr>
        <td><?= $position["datetime"] ?></td>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["transaction"] ?></td>
        <td class="alt"><?= $position["shares"] ?></td>
        <td class="alt"><?= $position["price"] ?></td>
    </tr>

<?php endforeach ?>

</table>
<br>
