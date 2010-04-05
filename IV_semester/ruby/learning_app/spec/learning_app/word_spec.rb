require File.join(File.dirname(__FILE__), '/../spec_helper') 

module LearningSystem
  describe Word do
    include WordSamples

    context "creating" do
      before(:each) do
        @good_word_samples = good_word_samples
        @bad_word_samples = bad_word_samples
      end

      context "creating valid words" do
        it "should create valid words" do
          @good_word_samples.each do |sample|
            lambda { Word.new(sample[:value], sample[:translation], sample[:hint])}.should_not raise_error
          end
        end
      end

      context "creating invalid words" do
        it "should raise an exception when invalid parameters are specified" do
          @bad_word_samples.each do |sample|
            lambda { Word.new(sample[:value], sample[:translation], sample[:hint])}.should raise_error
          end
        end
      end
    end

    context "guessing " do
      before(:each) do
        @word = Word.new("Test", "form of examination", "similar to quiz")
        @correct_value_guesses = ["Test", "TEST", "test", " test ", "test ", " test"]
        @correct_translation_guesses = ["FORM OF EXAMINATION", "form of examination", "FORM of Examination", " form of examintaion "]
      end

      it "should return true if guess was correct" do
        it "should be guessed by value"
          @correct_value_guesses.each do |answer|
            @word.guess_value(answer).should == true
          end
        end

        it "should be guessed by translation" do
          @correct_translation_guesses.each do |answer|
            @word.guess_translation(answer).should == true
          end
        end

      it "should return false if guess was incorrect" do
        @word.guess_value("quiz").should == false
        @word.guess_translation("quiz").should == false
      end

      context "counting guessing statistics" do
        it "should be guessed and answerred equally guessing by value" do
          @correct_value_guesses.each do |answer|
            @word.guess_value(answer)
          end

          @word.times_guessed.should == @correct_value_guesses.size
          @word.times_answered.should == @correct_value_guesses.size 
        end

        it "should be guessed and answerred equally guessing by translation" do
          @correct_translation_guesses.each do |answer|
            @word.guess_translation(answer)
          end

          @word.times_guessed.should == @correct_translation_guesses.size
          @word.times_answered.should == @correct_translation_guesses.size 
        end

        it "should be guessed 3 times and answerred 0 times" do
          2.times { @word.guess_value("quiz") }
          @word.guess_translation("quiz")

          @word.times_guessed.should == 3
          @word.times_answered.should == 0
        end
      end
    end
  end
end
