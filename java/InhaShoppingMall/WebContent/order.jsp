<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@page import="com.inhamall.dao.UserDao"%>
<%@page import="com.inhamall.model.User"%>
<!DOCTYPE html>
<html>
<head>
<title>주문하기</title>
<%
	String userid = (String)session.getAttribute("id");
	String productidx = request.getParameter("productidx");
	String qty = request.getParameter("qty");
	
	UserDao buyer_dao = new UserDao();
	User buyer = buyer_dao.getUserById(userid);
%>
<script>
function order(){
	var tmp = confirm("한번 주문하면 내용을 수정할 수 없습니다. 계속 하시겠습니까?");
	if(tmp) {
		alert("주문이 완료되었습니다. 결제에 대한 자세한 안내는 작성하신 연락처로 추후 안내 드리겠습니다. 감사합니다.")
	} else {
		alert("주문이 취소되었습니다.")
		return false;
	}
	return true;
}
</script>
</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%><!-- header.html 불러와서 사용(전 페이지 공통) -->
	</header>
	<%@ include file="layout/menubar.html"%><!-- menubar.html 불러와서 사용(전 페이지 공통) -->
	<br>
	<br>
	<center>
		<form method="post" action="OrderController" style="margin: 100px;" onsubmit="return order()">
		<br><br><br>
			<input type="text" name="userid" value="<%=userid %>" readonly="readonly" style="visibility: collapse;"/>
			<input type="text" name="productidx" value="<%=productidx %>" readonly="readonly" style="visibility: collapse;"/>
			
			<h3>수량</h3><input type="text" size="1" style="text-align: center;" name="qty" value="<%=qty %>" readonly="readonly"/><p>
			
			<h3>수령인 : <%=buyer.getUsername() %></h3>
			
			<h2>수령 주소</h2><input style="font-size: 15px" type="text" name="address" placeholder="주소" 
			maxlength="100" size="50" readonly="readonly" value="<%= buyer.getAddress()%>"><br>
			<span style="color: red;">※수령 주소가 다를경우, 회원정보 수정에서 변경해 주세요.</span>
			<p>
			
			<h2>연락처</h2>
			<input style="font-size: 15px; text-align: center;" type="text" name="passwd" placeholder="연락처" value="<%=buyer.getContact() %>"
				maxlength="16" size="15" readonly="readonly"><br>
			<span style="color: red;">※연락처가 다를경우, 회원정보 수정에서 변경해 주세요.</span>
				<p>
			
			<h2>배송 메모</h2>
			<textarea name="memo" id="memo" style="width: 450px; height: 150px;"></textarea><br>
			<span style="color;grey">ex.) 부재 시 문 앞에 놔주세요.</span>
			<p>
			 
			 <input type="submit" value="주문완료" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 
			 <input type="button" onclick="location.href='index.jsp'" value="주문 취소" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		
		</form>
	</center>
	<br>
	<br>
	<hr>

	<footer>
		<%@include file="layout/bottom.jsp"%><!-- footer.html 불러와서 사용(전페이지 공통) -->
	</footer>
	</body>
</html>