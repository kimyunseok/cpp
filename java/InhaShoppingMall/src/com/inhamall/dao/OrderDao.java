package com.inhamall.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.inhamall.model.Order;
import com.inhamall.model.Product;
import com.inhamall.util.DBUtil;

public class OrderDao {

	private Connection connection;

	public OrderDao() {
		connection = DBUtil.getConnection();
	}

	public void addOrder(Order order) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("insert into order_table (userid, productidx, qty, memo) VALUES (?, ?, ?, ?);");
			// Parameters start with 1
			preparedStatement.setString(1, order.getUserid());
			preparedStatement.setInt(2, order.getProductidx());
			preparedStatement.setInt(3, order.getQty());
			preparedStatement.setString(4, order.getMemo());
			preparedStatement.executeUpdate();
			
	    	ProductDao pdao = new ProductDao();
			Product product = pdao.getProductByIdx(order.getProductidx());
			product.setQty(product.getQty() - order.getQty());
			pdao.updateProduct(product);
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void deleteOrder(int orderidx) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("delete from order_table where orderidx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, orderidx);
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public Order getOrderByIdx(int orderidx) {
		Order Order = new Order();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from order_table where orderidx=?");
			preparedStatement.setInt(1, orderidx);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				Order.setOrderidx(rs.getInt("orderidx"));
				Order.setUserid(rs.getString("userid"));
				Order.setProductidx(rs.getInt("productidx"));
				Order.setQty(rs.getInt("qty"));
				Order.setMemo(rs.getString("memo"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return Order;
	}

	public List<Order> getAllOrders() {
		List<Order> Orders = new ArrayList<Order>();
		try {
			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery("select * from order_table");
			while (rs.next()) {
				Order Order = new Order();
				Order.setOrderidx(rs.getInt("orderidx"));
				Order.setUserid(rs.getString("userid"));
				Order.setProductidx(rs.getInt("productidx"));
				Order.setQty(rs.getInt("qty"));
				Order.setMemo(rs.getString("memo"));
				Orders.add(Order);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return Orders;
	}
	
	public List<Order> getOrdersByUserId(String userid) {
		List<Order> Orders = new ArrayList<Order>();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from order_table where userid=?");
			preparedStatement.setString(1, userid);
			ResultSet rs = preparedStatement.executeQuery();
			
			while (rs.next()) {
				Order Order = new Order();
				Order.setOrderidx(rs.getInt("orderidx"));
				Order.setUserid(rs.getString("userid"));
				Order.setProductidx(rs.getInt("productidx"));
				Order.setQty(rs.getInt("qty"));
				Order.setMemo(rs.getString("memo"));
				Orders.add(Order);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return Orders;
	}
	
}
