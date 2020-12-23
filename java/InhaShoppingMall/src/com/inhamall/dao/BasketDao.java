package com.inhamall.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.inhamall.model.Basket;
import com.inhamall.util.DBUtil;

public class BasketDao {

	private Connection connection;

	public BasketDao() {
		connection = DBUtil.getConnection();
	}

	public void addBasket(Basket basket) {
		try {
			
			PreparedStatement preparedStatement = connection
					.prepareStatement("insert into basket_table (userid, productidx, qty) VALUES (?, ?, ?);");
			// Parameters start with 1
			preparedStatement.setString(1, basket.getUserid());
			preparedStatement.setInt(2, basket.getProductidx());
			preparedStatement.setInt(3, basket.getQty());
			preparedStatement.executeUpdate();
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void deleteBasket(int basketidx) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("delete from basket_table where basketidx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, basketidx);
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public Basket getBasketByIdx(int basketidx) {
		Basket Basket = new Basket();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from basket_table where basketidx=?");
			preparedStatement.setInt(1, basketidx);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				Basket.setBasketidx(rs.getInt("basketidx"));
				Basket.setUserid(rs.getString("userid"));
				Basket.setProductidx(rs.getInt("productidx"));
				Basket.setQty(rs.getInt("qty"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return Basket;
	}

	public List<Basket> getBasketsByUserId(String userid) {
		List<Basket> Baskets = new ArrayList<Basket>();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from basket_table where userid=?");
			preparedStatement.setString(1, userid);
			ResultSet rs = preparedStatement.executeQuery();
			
			while (rs.next()) {
				Basket Basket = new Basket();
				Basket.setBasketidx(rs.getInt("basketidx"));
				Basket.setUserid(rs.getString("userid"));
				Basket.setProductidx(rs.getInt("productidx"));
				Basket.setQty(rs.getInt("qty"));
				Baskets.add(Basket);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return Baskets;
	}
	
}
