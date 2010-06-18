<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_panel/panel.css"/>
	</head>
	<body>
<?php
/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/

	session_start();
		
	$_SESSION['modulo'] = "panel";
	
	//require_once("../herramientas/GeneradorHtml.inc");
	//$html = new GeneradorHtml();
	$td_bienvenida = $html->tag("td", "class='alineacion_centro'", array("<label>Bienvenido, seleccione una de las opciones</label>"));
	$tr_bienvenida = $html->tag("tr", "", array($td_bienvenida));
	$table_bienvenida = $html->tag("table", "class='tbl_titulo tabla_centrada'", array($td_bienvenida));

  $contenido_modulo = "";
  if($viene_de_icono)//hizo click en el menu
    echo $table_bienvenida;
  else//actualizo la pagina f5
    $contenido_modulo = $table_bienvenida;

?>
	</body>
</html>