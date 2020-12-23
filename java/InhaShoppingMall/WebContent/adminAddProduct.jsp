<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

<title>관리자 상품 추가, 수정 페이지</title>
<script>
function checkBlank() {
	type = document.getElementById('producttype');
	name = document.getElementById('productname');
	img = document.getElementById('img');
	explanation = document.getElementById('explanation');
	price = document.getElementById('price');
	qty = document.getElementById('qty');
	
	if(type.value == "" || name.value == "" || explanation.value == "" 
			|| price.value == "" || qty.value == "" || img.value == "") {
		alert("공백인 값이 있습니다.\n별표가 쳐진 것들은 모두 작성해 주세요.");
		return false;
	} else {
		return true;
	}
}
</script>
</head>
<body>
<center>
<h1>상품 추가 페이지</h1><br>
     <div style="font-size: 20px"><b>
     <h3>상품 타입 설명</h3>
	 1x : 컴퓨터 노트북, 2x : PC장치(모니터 키보드 마우스), 3x : PC 주장치, 4x : 게이밍 관련</p>
	 
	 11 : 노트북 / 12 : 맥(애플) / 13 : 데스크탑 / 14: 태블릿 PC<br>
	 21 : 모니터 / 22 : 마우스 / 23 : 키보드 / 24 : 스피커 / 25 : 헤드폰<br>
	 31 : CPU / 32 : 램 / 33 : 그래픽카드 / 34 : 하드<br>
	 41 : 게이밍 장비 / 42 : 게임 / 43 : 공유기 / 44 : 프린터 / 45 : 기타<br>
	 </b>
	</div>
	</p>
		<form id="mainForm" name="mainForm" action="adminProductImageUpload.jsp" method="post" onsubmit="return checkBlank()" enctype="Multipart/form-data">
			<table width="800">
				<tr height="40">
					<td align="center" style="font-size: 45px; font-family: sans-serif;"><b><br>상품 추가</b></td>
				</tr>
			</table><br><br>
			<table width="700" heigh="600" cellpadding="0"
				style="border-collapse: collapse; font-size: 16px;">
				<tr class="addProduct" hegiht="30">
					<td width="5%" align="center">*</td>
					<td width="15%">제품 타입</td>
					<td><input type="text" size="2" id="producttype" name="producttype" maxlength="2"/>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">제품 이름</td>
					<td><input type="text" name="productname" id="productname" maxlength="75"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">이미지</td>
					<td><input type="file" name="img" id="img"/> <br>
					<span style="color: red"><b>이미지는 한번 선택하면 바꿀 수 없습니다.</b></span></td>
				</tr>

				
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">설명</td>
					<td><textarea name="explanation" id="explanation" style="width: 450px; height: 150px;"></textarea></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">가격</td>
					<td><input type="text" name="price" id="price" maxlength="9"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=addProduct " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">수량</td>
					<td><input type="text" name="qty" id="qty" maxlength="4"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
			</table>
			<br />
			<table>
			<tr><span id="notice" style="color: red;">상기내용 모두 다 꼭 써주셔야 합니다.</span></tr><br>
				<tr height="40">
					<td><input width="120" type="submit" value="상품추가" id="submit" style="border-radius: 5px; background-color: black; color: white;"/>&nbsp;</td>
					<td><input width="120" type="button" onclick="location.href='ProductController?action=listProduct'" value="취소" style="border-radius: 5px; background-color: black; color: white;"/></td>
				</tr>
			</table>
		</form>
	</center>

</body>
</html>