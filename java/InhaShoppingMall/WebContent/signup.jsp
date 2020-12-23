<%@page import="com.inhamall.dao.UserDao"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<link type="text/css" rel="stylesheet" href="style.css">
<title>회원가입</title>

<script>
	function checkBlank() {
		if(document.getElementById('name').value.length > 10) {
			alert("이름의 길이는 10자 이상이 될 수 없습니다.")
			document.getElementById('name').focus();
			return false;
		} else if(document.getElementById('name').value == "") {
			alert("이름은 빈 칸일 수 없습니다.")
			document.getElementById('name').focus();
			return false;
		} else if(document.getElementById('dob').value == "") {
			alert("생일은 빈 칸일 수 없습니다.")
			document.getElementById('dob').focus();
			return false;
		} else {
			alert("회원가입이 완료되었습니다.");
			return true;
		}
	}
	function idchange() {
		if(document.getElementById('id').value.length >= 6) {
		idok = false;
		document.getElementById('idoverLapText').innerHTML = "ID중복체크를 하세요"
		document.getElementById('submit').disabled = true;
		notice.innerHTML = "아이디 중복검사를 해주세요!"
		notice.style.color = "red";
		submit.style.background = "grey";
		}
	}

	function idoverlap() {
	window.open('idSearchForm.jsp?id=' + document.getElementById('id').value, 'w', 'width=500px, height=500px, left=400px, top=100px');
	} 
	
	var pwok = false;
	var idok = false;
	
	function idpwCheck() {
	id = document.getElementById('id');
	pw = document.getElementById('pw');
	pwCheck = document.getElementById('pwCheck');
	notice = document.getElementById('notice');
	submit = document.getElementById('submit');
	idoverLapText = document.getElementById('idoverLapText');
	
	 if(idoverLapText.innerHTML != "ID 사용가능!") {
		idok = false;
		document.getElementById('submit').disabled = true;
		notice.innerHTML = "아이디 중복검사를 해주세요!"
		notice.style.color = "red";
		submit.style.background = "grey";
	}
	 
	if(pw.value.length < 6) {
		pwok = false;
		document.getElementById('submit').disabled = true;
		notice.innerHTML = "비밀번호가 너무 짧습니다!<br>비밀번호는 최소 6글자입니다."
		notice.style.color = "red";
		submit.style.background = "grey";
	} else {
	if(pw.value == pwCheck.value) {
		pwok = true;
		if(idok) {
		document.getElementById('submit').disabled = false;
		notice.innerHTML = ""
		submit.style.background = "black";
		}
	} else {
		pwok = false;
		document.getElementById('submit').disabled = true;
		notice.innerHTML = "비밀번호가 다릅니다!"
		notice.style.color = "red";
		submit.style.background = "grey";
	}
	
	}
	if(id.value.length < 6 || id.value.length > 12) {
		idok = false;
		document.getElementById('submit').disabled = true;
		notice.innerHTML = "아이디가 너무 길거나 짧습니다!<br>아이디는 최소 6글자 최대 12글자입니다."
		document.getElementById('idover').disabled = true;
		notice.style.color = "red";
		submit.style.background = "grey";
		document.getElementById('idover').style.background = "grey";
	}
	else {
		idok = true;
		document.getElementById('idover').disabled = false;
		document.getElementById('idover').style.background = "black";
		if(pwok){
		document.getElementById('submit').disabled = false;
		notice.innerHTML = ""
		submit.style.background = "black";
		}
	}
	
	for(var i = 0; i < id.value.length; i++) {
		if( !( (id.value.charAt(i) >= 'a' && id.value.charAt(i) <= 'z') || (id.value.charAt(i) >= '0' && id.value.charAt(i) <= '9') ||
				(id.value.charAt(i) >= 'A' && id.value.charAt(i) <= 'Z') ) ) {
			idok = false;
			document.getElementById('submit').disabled = true;
			document.getElementById('idover').disabled = true;
			document.getElementById('idover').style.background = "grey";
			notice.innerHTML = "아이디에 특수문자가 들어가있습니다!<br>아이디는 영어 대소문자와 숫자만 사용가능합니다."
			notice.style.color = "red";
			submit.style.background = "grey";
		} 
	}
	
	}
</script>

</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%>
	</header>

	<center>
		<form action="UserController" method="post" onsubmit="return checkBlank()">
			<table width="800">
				<tr height="40">
					<td align="center" style="font-size: 45px; font-family: sans-serif;"><b><br>회원가입</b></td>
				</tr>
			</table><br><br>
			<table width="700" heigh="600" cellpadding="0"
				style="border-collapse: collapse; font-size: 16px;">
				<tr class="register" hegiht="30">
					<td width="5%" align="center">*</td>
					<td width="15%">회원 ID</td>
					<td><input type="text" size="10	" id="id" name="id" onchange="idpwCheck(); idchange()" maxlength="12"/>&nbsp
					<input type="button" style="border-radius: 5px; background-color: grey; color: white;" id="idover" onclick="idoverlap()" value="ID중복체크" disabled="disabled"/>
					<span id="idoverLapText">ID중복체크를 하세요</span>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">비밀번호</td>
					<td><input type="password" name="password" id="pw"
						onchange="idpwCheck()" maxlength="25"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">비밀번호 확인</td>
					<td><input type="password" name="passwordCheck" id="pwCheck"
						onchange="idpwCheck()"  maxlength="25"/>&nbsp;&nbsp;</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">이 름</td>
					<td><input type="text" name="name" id="name" onchange="idpwCheck()" maxlength="10"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center">*</td>
					<td width="15%">생일</td>
					<td><input type="date" name="dob" id="dob" style="font-size: 16px;"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">성 별</td>
					<td>남자<input type="radio" name="sex" value="남자"
						checked /> &nbsp;여자<input type="radio" name="sex"
						value="여자" />
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">휴대전화</td>
					<td><input type="text" name="contact" id="wUserCellPhone" maxlength="20"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">이메일</td>
					<td><input type="text" name="email" maxlength="25"/><a style="text-align: right; font-size: 9px;">※ 이메일과 휴대전화는 아이디, 비밀번호를 찾는데 사용됩니다.</a></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">주소</td>
					<td><input type="text" name="address" id="address" maxlength="100" size="80" 
					placeholder="주소 (상세하게 적어주세요.)"/></td>
				</tr>
			</table>
			<br />
			<table>
			<tr><span id="notice" style="color: red;"></span></tr>
				<tr height="40">
					<td><input width="120" type="submit" value="회원가입" id="submit" style="border-radius: 5px; background-color: grey; color: white;" disabled="disabled"/>&nbsp;</td>
					<td><a href="index.jsp"><input width="120" type="button" value="취소" style="border-radius: 5px; background-color: black; color: white;"/></a></td>
				</tr>
			</table>
		</form>
	</center>

	<hr>

	<footer>
		<%@include file="layout/bottom.jsp"%><!-- footer.html 불러와서 사용(전페이지 공통) -->
	</footer>
</html>
