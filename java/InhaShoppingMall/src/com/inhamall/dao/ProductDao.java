package com.inhamall.dao;

import java.io.File;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.inhamall.model.Product;
import com.inhamall.util.DBUtil;

public class ProductDao {

	private Connection connection;

	public ProductDao() {
		connection = DBUtil.getConnection();
	}

	public void addProduct(Product product) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("insert into product_table (producttype, productname, img, explanation, price, qty) VALUES (?, ?, ?, ?, ?, ?);");
			// Parameters start with 1
			preparedStatement.setInt(1, product.getProducttype());
			preparedStatement.setString(2, product.getProductname());
			preparedStatement.setString(3, product.getImg());
			preparedStatement.setString(4, product.getExplanation());
			preparedStatement.setInt(5, product.getPrice());
			preparedStatement.setInt(6, product.getQty());
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void deleteProduct(int productidx, String dir) {
		try {
			Product product = getProductByIdx(productidx);
			File f = new File(dir + "\\" + product.getImg());
			if(f.exists()) {
				f.delete();
			}
			PreparedStatement preparedStatement = connection
					.prepareStatement("delete from product_table where productidx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, productidx);
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public Product getProductByIdx(int productidx) {
		Product product = new Product();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from product_table where productidx=?");
			preparedStatement.setInt(1, productidx);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				product.setProductidx(rs.getInt("productidx"));
				product.setProducttype(rs.getInt("producttype"));
				product.setProductname(rs.getString("productname"));
				product.setImg(rs.getString("img"));
				product.setExplanation(rs.getString("explanation"));
				product.setPrice(rs.getInt("price"));
				product.setQty(rs.getInt("qty"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return product;
	}
	
	public void updateProduct(Product product) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("update product_table set producttype=?, productname=?, img=?, explanation=?, price=?, qty=? where productidx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, product.getProducttype());
			preparedStatement.setString(2, product.getProductname());
			preparedStatement.setString(3, product.getImg());
			preparedStatement.setString(4, product.getExplanation());
			preparedStatement.setInt(5, product.getPrice());
			preparedStatement.setInt(6, product.getQty());
			preparedStatement.setInt(7, product.getProductidx());
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public List<Product> getAllProducts() {
		List<Product> products = new ArrayList<Product>();
		try {
			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery("select * from product_table");
			while (rs.next()) {
				Product product = new Product();
				product.setProductidx(rs.getInt("productidx"));
				product.setProducttype(rs.getInt("producttype"));
				product.setProductname(rs.getString("productname"));
				product.setImg(rs.getString("img"));
				product.setExplanation(rs.getString("explanation"));
				product.setPrice(rs.getInt("price"));
				product.setQty(rs.getInt("qty"));
				products.add(product);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return products;
	}
	
	public List<Product> getProductsByType(int producttype) {
		List<Product> products = new ArrayList<Product>();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from product_table where producttype=?");
			preparedStatement.setInt(1, producttype);
			ResultSet rs = preparedStatement.executeQuery();
			
			while (rs.next()) {
				Product product = new Product();
				product.setProductidx(rs.getInt("productidx"));
				product.setProducttype(rs.getInt("producttype"));
				product.setProductname(rs.getString("productname"));
				product.setImg(rs.getString("img"));
				product.setExplanation(rs.getString("explanation"));
				product.setPrice(rs.getInt("price"));
				product.setQty(rs.getInt("qty"));
				products.add(product);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return products;
	}
	
}
