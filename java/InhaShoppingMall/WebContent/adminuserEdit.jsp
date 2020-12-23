<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

<title>회원정보수정</title>
<script>
	function checkpw() {
		pw = document.getElementById('pw');
		pwCheck = document.getElementById('pwCheck');
		if(pw.value != pwCheck.value) {
			alert("비밀번호가 다릅니다.");
			document.getElementById('pw').focus();
			return false;
		} else if(pw.value.length < 6) {
			alert("비밀번호의 길이가 너무 짧습니다.비밀번호는 최소 6글자입니다.");
			document.getElementById('pw').focus();
			return false;
		}
		else {
			alert("회원정보 수정이 완료되었습니다.");
			return true;
		}
	}
</script>
</head>
<body>

	<jsp:useBean id = "user" class="com.inhamall.model.User" scope="request"></jsp:useBean>
	<jsp:setProperty property="*" name="user"/>
	
	
<center>
		<form action="UserController" method="post" onsubmit="return checkpw()">
			<table width="800">
				<tr height="40">
					<td align="center" style="font-size: 30px; font-family: sans-serif;"><b><br>관리자 회원정보 수정</b></td>
				</tr>
			</table><br><br>
			<table width="700" heigh="600" cellpadding="0"
				style="border-collapse: collapse; font-size: 16px;">
				<tr class="register" hegiht="30">
					<td width="5%" align="center"> </td>
					<td width="15%">회원 인덱스</td>
					<td><input type="text" name="useridx"  
					value="<jsp:getProperty property="useridx" name="user"/>"/>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class="register" hegiht="30">
					<td width="5%" align="center"> </td>
					<td width="15%">회원 등급</td>
					<td><input type="text" name="usertype"  
					value="<jsp:getProperty property="usertype" name="user"/>"/><br><span>0 : 일반회원, 1 : 실버, 2 : 골드, 3 : 플레티넘, 4 : V.I.P, 5 : 운영진</span>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class="register" hegiht="30">
					<td width="5%" align="center"> </td>
					<td width="15%">회원 ID</td>
					<td><input type="text" size="10	" id="id" name="id"
					value="<jsp:getProperty property="id" name="user"/>"/>
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">비밀번호</td>
					<td><input type="text" name="password" id="pw"
					value="<jsp:getProperty property="password" name="user"/>"/>
					
					</td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">이 름</td>
					<td><input type="text" name="name" id="name"
					value="<jsp:getProperty property="username" name="user"/>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">생일</td>
					<td><input type="date" name="dob" id="dob" style="font-size: 16px;"
					value="<jsp:getProperty property="dob" name="user"/>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">성 별</td>
					<td><input type="text" name="sex" id="sex" style="font-size: 16px;"
					value="<jsp:getProperty property="sex" name="user"/>"/></td>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">휴대전화</td>
					<td><input type="tel" name="contact" id="wUserCellPhone"
					value="<jsp:getProperty property="contact" name="user"/>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">이메일</td>
					<td><input type="email" name="email"
					value="<jsp:getProperty property="email" name="user"/>"/><a style="text-align: right; font-size: 9px;">※ 이메일과 휴대전화는 아이디, 비밀번호를 찾는데 사용됩니다.</a></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				<tr class=register " height="30">
					<td width="5%" align="center"> </td>
					<td width="15%">주소</td>
					<td><input type="text" name="address" id="address" maxlength="100" size="80" 
					placeholder="주소 (상세하게 적어주세요.)" value="<jsp:getProperty property="address" name="user"/>"/></td>
				</tr>
				<tr height="7">
					<td colspan="3"><hr /></td>
				</tr>
				
			</table>
			<br />
			<table>
			<tr><span id="notice" style="color: red;"></span></tr>
				<tr height="40">
					<td><input width="120" type="submit" value="수정완료" id="submit" style="border-radius: 5px; background-color: black; color: white;"/>&nbsp;</td>
					<td><input width="120" onclick="location.href='UserController?action=listUser'" type="button" value="취소" style="border-radius: 5px; background-color: black; color: white;"/></td>
				</tr>
			</table>
		</form>
	</center>

</body>
</html>