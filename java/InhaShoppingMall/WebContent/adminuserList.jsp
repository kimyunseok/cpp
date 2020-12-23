<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>유저 리스트</title>
</head>
<body>
<center>
<h1>회원 리스트 페이지</h1>
    <input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
    </p>
    <table cellpadding="10"
				style="border-collapse: collapse; font-size: 16px;" border="5">
        <thead style="background: black; color: white;">
            <tr>
                <th>Idx</th>
                <th>회원 등급</th>
                <th>ID</th>
                <th>비밀번호</th>
                <th>이름</th>
                <th>생일</th>
                <th>성별</th>
                <th>연락처</th>
                <th>주소</th>
                <th>이메일</th>
                <th colspan=2>편집</th>
            </tr>
        </thead>
        <tbody>
            <c:forEach items="${users}" var="user">
                <tr>
                    <td><c:out value="${user.useridx}" /></td>
                    <td><c:out value="${user.usertype}" /></td>
                    <td><c:out value="${user.id}" /></td>
                    <td><c:out value="${user.password}" /></td>
                    <td><c:out value="${user.username}" /></td>
                    <td><c:out value="${user.dob}" /></td>
                    <td><c:out value="${user.sex}" /></td>
                    <td><c:out value="${user.contact}" /></td>
                    <td><c:out value="${user.address}" /></td>
                    <td><c:out value="${user.email}" /></td>
                    <td style="background: blue;"><a style="color: white" href="UserController?action=adminedit&useridx=<c:out value="${user.useridx}"/>">수정</a></td>
                    <td style="background: red;"><a style="color: white" href="UserController?action=delete&useridx=<c:out value="${user.useridx}"/>">삭제</a></td>
                </tr>
            </c:forEach>
        </tbody>
    </table>
    </center>
</body>
</html>