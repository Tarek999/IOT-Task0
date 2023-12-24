class MeasuresController < ApplicationController
    def index
        @measures = Measure.all
    
        render json: @measures, status: :ok
      end
    
      def show
        @measure = Measure.find(params[:id])
    
        render json: @measure, status: :ok
      end
    
      def create
        @measure = Measure.create!(measures_params)
    
        render json: @measure, status: 201
      end
    
      #   def update
      #     jogging_record_parameters = jogging_record_params
      #     jogging_record_parameters[:user_id] = current_user.id if current_user.user?
    
      #     @jogging_record = policy_scope(JoggingRecord).find(params[:id])
      #     @jogging_record.update!(jogging_record_parameters)
    
      #     render json: decorate, status: :ok
      #   end
    
      #   def destroy
      #     policy_scope(JoggingRecord).find(params[:id]).destroy!
    
      #     render json: { message: "JoggingRecord with id: #{params[:id]} has been deleted successfully" }, status: 202
      #   end
    
      def measures_params
        params.permit(:measure, :time, :measure_type)
      end
end
